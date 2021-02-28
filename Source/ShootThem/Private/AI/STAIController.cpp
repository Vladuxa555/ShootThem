// Shoot Them Game, All Right Reserved


#include "AI/STAIController.h"
#include "AI/STAICharacter.h"

void ASTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STCharacter= Cast<ASTAICharacter>(InPawn);
	if(STCharacter)
	{
		RunBehaviorTree(STCharacter->BehaviorTreeAsset);
	}
}
