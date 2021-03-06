// Shoot Them Game, All Right Reserved


#include "UI/STGameDataWidget.h"
#include "STGameModeBase.h"
#include "STPlayerHUDWidget.h"
#include "STPlayerState.h"

int32 USTGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetSTPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetSTGameMode();
	return GameMode ? GameMode->GetRoundSecondRamining() : 0;
}

ASTGameModeBase* USTGameDataWidget::GetSTGameMode() const
{
	return GetWorld() ? Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTPlayerState* USTGameDataWidget::GetSTPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
