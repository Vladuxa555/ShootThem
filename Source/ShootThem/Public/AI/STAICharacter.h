// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STBaseCharacter.h"
#include "STAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;
UCLASS()
class SHOOTTHEM_API ASTAICharacter : public ASTBaseCharacter
{
	GENERATED_BODY()
public:
	ASTAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	float HealthVisibilityDistance = 1000.0f;
	
	virtual void BeginPlay() override;

	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;
	private:
	void UpdateHealthWidgetVisibility();
};
