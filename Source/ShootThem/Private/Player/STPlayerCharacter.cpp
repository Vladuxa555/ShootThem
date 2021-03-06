// Shoot Them Game, All Right Reserved


#include "Player/STPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STWeaponComponent.h"
#include "Components/SphereComponent.h"
#include  "Components/CapsuleComponent.h"

ASTPlayerCharacter::ASTPlayerCharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;
	SpringArmComponent->SocketOffset = FVector(0.f,100.0f,80.0f);
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
void ASTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this,&ASTPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this,&ASTPlayerCharacter::OnCameraCollisionEndOverlap);
}
void ASTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);
	check(GetCapsuleComponent());
	check(GetMesh());
	
	PlayerInputComponent->BindAxis("MoveForward",this,&ASTPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASTPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this,&ASTPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround",this,&ASTPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASTPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASTPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ASTPlayerCharacter::OnStopRun);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,WeaponComponent,&USTWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released,WeaponComponent,&USTWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon",IE_Pressed,WeaponComponent,&USTWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload",IE_Pressed,WeaponComponent,&USTWeaponComponent::Reload);
}
void ASTPlayerCharacter::MoveForward(float Amount)
{
	IsMoveForward = Amount > 0.0f;
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(),Amount);
}

void ASTPlayerCharacter::OnStartRun()
{
	WantsToRun=true;
}
void ASTPlayerCharacter::OnStopRun()
{
	WantsToRun=false;
}

void ASTPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASTPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASTPlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true,MeshChildren);

	for(auto MeshChild: MeshChildren)
	{
		const auto MeshChildGeomtry = Cast<UPrimitiveComponent>(MeshChild);
		if(MeshChildGeomtry)
		{
			MeshChildGeomtry->SetOwnerNoSee(HideMesh);
		}
	}
}

bool ASTPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMoveForward && !GetVelocity().IsZero();
}

void ASTPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}


