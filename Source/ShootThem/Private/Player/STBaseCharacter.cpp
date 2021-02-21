// Shoot Them Game, All Right Reserved


#include "Player/STBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STCharacterMovementComponent.h"

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
}

// Called when the game starts or when spawned
void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASTBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMoveForward && !GetVelocity().IsZero();
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
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTBaseCharacter::MoveRight(float Amount)
{
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