// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STCoreTypes.h"
#include "STGameInstance.generated.h"

UCLASS()
class SHOOTTHEM_API USTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FLevelData GetStartUpLevel() const { return StartUpLevel; }
	void SetStartUpLevel(const FLevelData& Data) { StartUpLevel = Data; }

	TArray<FLevelData> GetLevelsData() const {return LevelsData;}
	
	FName GetMenuLevelName() const { return MenuLevelName; }
protected:

	UPROPERTY(EditDefaultsOnly,Category="Game",meta =(ToolTip = "Level names must be unique"))
	TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly,Category="Game")
	FName MenuLevelName = NAME_None;

private:
	FLevelData StartUpLevel;
};
