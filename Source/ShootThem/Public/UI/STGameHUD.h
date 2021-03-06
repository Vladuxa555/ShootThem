// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STCoreTypes.h"
#include "GameFramework/HUD.h"
#include "STGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTGameHUD : public AHUD
{
	GENERATED_BODY()
	public:
	virtual void DrawHUD() override;

	protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

	private:
	UPROPERTY()
	TMap <ESTMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
	
	void DrawCrossHair();
	void OnMatchStateChanged(ESTMatchState State);
};
