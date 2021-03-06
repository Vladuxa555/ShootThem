// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "STPlayerController.generated.h"

class USTRespawnComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	ASTPlayerController();
	protected:
	UPROPERTY(VisibleAnywhere ,BlueprintReadWrite,Category="Components")
	USTRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	private:
	void OnPauseGame();
	void OnMatchStateChanged(ESTMatchState State);
};
