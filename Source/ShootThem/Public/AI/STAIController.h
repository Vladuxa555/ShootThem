// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STAIController.generated.h"

class USTRespawnComponent;
class USTAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTAIController : public AAIController
{
	GENERATED_BODY()
	public:
	ASTAIController();
	protected:
	UPROPERTY(VisibleAnywhere ,BlueprintReadWrite,Category="Components")
	USTAIPerceptionComponent* STAIPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere ,BlueprintReadWrite,Category="Components")
	USTRespawnComponent* RespawnComponent;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	private:
	AActor* GetFocusOnActor() const;
	
};
