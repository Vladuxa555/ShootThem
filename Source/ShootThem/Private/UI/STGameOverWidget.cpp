// Shoot Them Game, All Right Reserved


#include "UI/STGameOverWidget.h"
#include "STGameModeBase.h"
#include "Player/STPlayerState.h"
#include "UI/STPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this,&USTGameOverWidget::OnMatchStateChanged);
		}
	}
	if(ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this,&USTGameOverWidget::OnResetLevel);
	}
}

void USTGameOverWidget::OnMatchStateChanged(ESTMatchState State)
{
	if(State == ESTMatchState::GameOver)
	{}
	UpdatePlayersStat();
}

void USTGameOverWidget::UpdatePlayersStat()
{
	if(!GetWorld()||!PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for(auto It=GetWorld()->GetControllerIterator();It;++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<USTPlayerStatRowWidget>(GetWorld(),PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(STUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(STUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget->SetTeam(STUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void USTGameOverWidget::OnResetLevel()
{
	//const FName CurrentLevelName = "TestLevel";
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this,FName(CurrentLevelName));
	
}
