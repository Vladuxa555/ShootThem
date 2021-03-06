// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STCoreTypes.h"
#include "STLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
UCLASS()
class SHOOTTHEM_API USTLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const {return LevelData;}

	void SetSelected(bool IsSelected);
	protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

	virtual void NativeOnInitialized() override;

	private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelItemClicked();
};
