// Shoot Them Game, All Right Reserved


#include "STGameModeBase.h"

#include <tuple>

#include "Player/STPlayerController.h"
#include "Player/STBaseCharacter.h"
#include "UI/STGameHUD.h"
#include "AI/STAIController.h"
#include "Player/STPlayerState.h"
#include "STUtils.h"
#include "Components/STRespawnComponent.h"
#include "EngineUtils.h"
#include "STPlayerCharacter.h"
#include "GenericPlatform/GenericApplication.h"
#include "STGameInstance.h"

constexpr static int32 MinRoundTimeForRespawn = 10;

DEFINE_LOG_CATEGORY_STATIC(LogSTGameModeBase ,All, All);

ASTGameModeBase::ASTGameModeBase()
{
	DefaultPawnClass=ASTPlayerCharacter::StaticClass();
	PlayerControllerClass=ASTPlayerController::StaticClass();
	HUDClass=ASTGameHUD::StaticClass();
	PlayerStateClass = ASTPlayerState::StaticClass();
}

UClass* ASTGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController &&InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTGameModeBase::StartPlay()
{
	Super::StartPlay();

	
	SpawnBots();
	CreateTeamsInfo();
	
	CurrentRound = 1;
	StartRound();

	SetMatchState(ESTMatchState::InProgress);
}



void ASTGameModeBase::SpawnBots()
{
	if(!GetWorld()) return;
	
	for(int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STAIController=GetWorld()->SpawnActor<AAIController>(AiControllerClass,SpawnInfo);
		RestartPlayer(STAIController);

	}
}

void ASTGameModeBase::StartRound()
{
	RoundCountDawn = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle,this,&ASTGameModeBase::GameTimerUpdate, 1.0, true);
}

void ASTGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogSTGameModeBase,Display,TEXT("Time: %i /Round: %i/%i"),RoundCountDawn,CurrentRound,GameData.RoundsNum);
	if(--RoundCountDawn == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if(CurrentRound + 1<= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTGameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTGameModeBase::ResetOnePlayer(AController* Controller)
{
	if(Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTGameModeBase::CreateTeamsInfo()
{
	if(!GetWorld()) return;

	int32 TeamID = 1;
	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if(TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogSTGameModeBase,Warning,TEXT("No color fore team id: %i, set to default: %s"),TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASTGameModeBase::SetPlayerColor(AController* Controller)
{
	if(!Controller) return;
	const auto Character = Cast<ASTBaseCharacter>(Controller->GetPawn());
	if(!Character) return;

	const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
	if(!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASTPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASTPlayerState>(VictimController->PlayerState) : nullptr;

	if(KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if(VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	StartRespawn(VictimController);
}



void ASTGameModeBase::LogPlayerInfo()
{
	if(!GetWorld()) return;
	
	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void ASTGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}
void ASTGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvaliable = RoundCountDawn > MinRoundTimeForRespawn + GameData.RespawnTme;
	if(!RespawnAvaliable) return;
	const auto RespawnComponent = STUtils::GetSTPlayerComponent<USTRespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTme);
}

void ASTGameModeBase::GameOver()
{
	UE_LOG(LogSTGameModeBase,Display,TEXT("======Game Over======="));
	LogPlayerInfo();

	for(auto Pawn: TActorRange<APawn>(GetWorld()))
	{
		if(Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(ESTMatchState::GameOver);
}

void ASTGameModeBase::SetMatchState(ESTMatchState State)
{
	if(MatchState == State) return;

	MatchState = State;
	OnMatchStateChangedSignature.Broadcast(MatchState);
}
bool ASTGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if(PauseSet)
	{
		SetMatchState(ESTMatchState::Pause);
	}
	return PauseSet;
}

bool ASTGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if(PauseCleared)
	{
		SetMatchState((ESTMatchState::InProgress));
	}
	return PauseCleared;
}
