// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STGameModeBase.h"
#include "STPlayerController.h"
#include "STPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "STGameDataWidget.generated.h"

class ASTGameModeBase;
class ASTPlayerState;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	ASTGameModeBase* GetSTGameMode() const;
	ASTPlayerState* GetSTPlayerState() const;
};
