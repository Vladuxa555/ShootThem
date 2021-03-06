// Shoot Them Game, All Right Reserved


#include "UI/STPlayerHUDWidget.h"
#include "Components/STHealthComponent.h"
#include "Components/STWeaponComponent.h"
#include"STUtils.h"
float USTPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTPlayerHUDWidget::GetCurrentWeaponUiData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUiData(UIData);
}

bool USTPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTPlayerHUDWidget::NativeOnInitialized()
{
	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this,&USTPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void USTPlayerHUDWidget::OnHealthChanged(float Health,float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
		OnTakeDamage();
	} 
}

void USTPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(NewPawn);
	if(HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this,&USTPlayerHUDWidget::OnHealthChanged);
	}
}

