// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEM_API USTGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(meta=(BindWidget))
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;
	private:
	UFUNCTION()
	void OnGoToMenu();
};
