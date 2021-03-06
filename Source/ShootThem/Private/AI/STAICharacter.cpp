// Shoot Them Game, All Right Reserved


#include "AI/STAICharacter.h"
#include "STAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STAIWeaponComponent.h"
#include "BrainComponent.h"
#include"Components/WidgetComponent.h"
#include"Components/STHealthComponent.h"
#include "UI/STHealthBarWidget.h"

ASTAICharacter::ASTAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<USTAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,200.0f,0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateHealthWidgetVisibility();
}



void ASTAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void ASTAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthBarWidget = Cast<USTHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());

	if(!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASTAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STController = Cast<AAIController>(Controller);
	if(STController && STController->BrainComponent)
	{
		STController->BrainComponent->Cleanup();
	}
}

void ASTAICharacter::UpdateHealthWidgetVisibility()
{
	if(!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation,GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance,true);
}