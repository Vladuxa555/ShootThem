// Shoot Them Game, All Right Reserved


#include "UI/STSpectatorWidget.h"
#include "STUtils.h"
#include "Components/STRespawnComponent.h"

bool USTSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = STUtils::GetSTPlayerComponent<USTRespawnComponent>(GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
