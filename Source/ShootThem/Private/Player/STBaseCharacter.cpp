// Shoot Them Game, All Right Reserved


#include "Player/STBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STCharacterMovementComponent.h"
#include "Components/STHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog,All,All);

// Sets default values
ASTBaseCharacter::ASTBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTHealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASTBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTBaseCharacter::OnHealthChanged);
}

bool ASTBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMoveForward && !GetVelocity().IsZero();
}

float ASTBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero())return 0.0f;
	const auto VelocityNormal= GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees*FMath::Sign(CrossProduct.Z);
}

// Called every frame
void ASTBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ASTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASTBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASTBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this,&ASTBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround",this,&ASTBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASTBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASTBaseCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ASTBaseCharacter::OnStopRun);
 
}

void ASTBaseCharacter::MoveForward(float Amount)
{
	IsMoveForward = Amount > 0.0f;
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(),Amount);
}

void ASTBaseCharacter::OnStartRun()
{
	WantsToRun=true;
}
void ASTBaseCharacter::OnStopRun()
{
	WantsToRun=false;
}

void ASTBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog,Display,TEXT("Player %s is dead"), *GetName());

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}


