// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "STGameModeBase.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTGameModeBase();
	FOnMatchStateChangedSignature OnMatchStateChangedSignature;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual void StartPlay() override;

	void Killed(AController* KillerController, AController* VictimController);

	FGameData GetGameData() const {return GameData;}
	int32 GetCurrentRoundNum() const {return CurrentRound;}
	int32 GetRoundSecondRamining() const {return RoundCountDawn;}

	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause())override;
	virtual bool ClearPause() override;
protected:
	UPROPERTY(EditDefaultsOnly,Category="Game")
	TSubclassOf<AAIController> AiControllerClass;

	UPROPERTY(EditDefaultsOnly,Category="Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly,Category="Game")
	FGameData GameData;
private:
	ESTMatchState MatchState = ESTMatchState::WaitingToStart;
	int32 CurrentRound = 1;
	int32 RoundCountDawn = 1;
	FTimerHandle GameRoundTimerHandle;
	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();

	void SetMatchState(ESTMatchState State);
};
