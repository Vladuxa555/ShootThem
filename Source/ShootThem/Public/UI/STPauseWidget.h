// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEM_API USTPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;
	virtual void NativeOnInitialized() override;
	private:
	UFUNCTION()
	void OnClearPause();
};
