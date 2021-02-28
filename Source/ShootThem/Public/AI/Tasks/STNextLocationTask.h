// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	public:
	USTNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector AimLocationKey;
};
