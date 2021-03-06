// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STCoreTypes.h"
#include "STMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTGameInstance;
class USTLevelItemWidget;

UCLASS()
class SHOOTTHEM_API USTMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TArray<USTLevelItemWidget*> LevelItemWidgets;
	
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
    void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USTGameInstance* GetSTGameInstance() const;
};
