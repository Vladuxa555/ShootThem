// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTFindEnemyService : public UBTService
{
	GENERATED_BODY()
	public:
	USTFindEnemyService();
	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyActorKey;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
