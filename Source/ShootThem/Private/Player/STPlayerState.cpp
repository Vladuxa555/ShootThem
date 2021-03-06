// Shoot Them Game, All Right Reserved


#include "Player/STPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTPlayerState ,All, All);

void ASTPlayerState::LogInfo()
{
	UE_LOG(LogSTPlayerState,Display,TEXT("TeamID: %i, Kills: %i, Deaths: %i"),TeamID, KillsNum, DeathsNum);
}
