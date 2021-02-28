// Shoot Them Game, All Right Reserved


#include "AI/STAIController.h"
#include "AI/STAICharacter.h"
#include "Components/STAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTAIController::ASTAIController()
{
	STAIPerceptionComponent = CreateDefaultSubobject<USTAIPerceptionComponent>("STPerceptionComponent");
	SetPerceptionComponent(*STAIPerceptionComponent);
}

void ASTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STCharacter= Cast<ASTAICharacter>(InPawn);
	if(STCharacter)
	{
		RunBehaviorTree(STCharacter->BehaviorTreeAsset);
	}
}

void ASTAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ASTAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
