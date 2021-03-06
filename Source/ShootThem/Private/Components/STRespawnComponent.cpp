// Shoot Them Game, All Right Reserved


#include "Components/STRespawnComponent.h"
#include "STGameModeBase.h"

USTRespawnComponent::USTRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	

}

void USTRespawnComponent::Respawn(int32 RespawnTime)
{
	if(!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle,this,&USTRespawnComponent::RespawnTimerUpdate,1.0f,true);
	
}


void USTRespawnComponent::RespawnTimerUpdate()
{
	if(--RespawnCountDown == 0)
	{
		if(!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}


bool USTRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}