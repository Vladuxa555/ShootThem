// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	public:
	AActor* GetClosestEnemy() const;
	
};
