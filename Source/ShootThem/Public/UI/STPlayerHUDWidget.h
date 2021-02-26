// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintCallable,Category="UI")
	float GetHealthPercent()const;
	
	UFUNCTION(BlueprintCallable,Category="UI")
	bool GetCurrentWeaponUiData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable,Category="UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable,Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable,Category="UI")
    bool IsPlayerSpectating() const;
};
