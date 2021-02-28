// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STBaseCharacter.h"
#include "STAICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTAICharacter : public ASTBaseCharacter
{
	GENERATED_BODY()
	public:
	ASTAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
};
