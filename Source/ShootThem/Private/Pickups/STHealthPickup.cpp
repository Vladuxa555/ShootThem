// Shoot Them Game, All Right Reserved


#include "Pickups/STHealthPickup.h"
#include "Components/STHealthComponent.h"
#include "STUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup,All,All);

bool ASTHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUtils::GetSTPlayerComponent<USTHealthComponent>(PlayerPawn);
	if(!HealthComponent) return false;
	return HealthComponent->TryToAddHealth(HealthAmount);
}