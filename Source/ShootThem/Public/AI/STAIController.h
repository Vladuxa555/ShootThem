// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTAIController : public AAIController
{
	GENERATED_BODY()
	protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
