// Shoot Them Game, All Right Reserved


#include "AI/STAICharacter.h"
#include "STAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTAICharacter::ASTAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,200.0f,0.0f);
	}
}
