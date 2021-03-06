// Shoot Them Game, All Right Reserved


#include "Menu/UI/STMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "STGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/UI/STLevelItemWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTMenuWidget ,All, All);

void USTMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this,&USTMenuWidget::OnStartGame);
	}
	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this,&USTMenuWidget::OnQuitGame);
	}
	InitLevelItems();
}

void USTMenuWidget::OnStartGame()
{
	const auto STGameInstance = GetSTGameInstance();
	if(!STGameInstance) return;
	UGameplayStatics::OpenLevel(this,STGameInstance->GetStartUpLevel().LevelName);
}

void USTMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this,GetOwningPlayer(), EQuitPreference::Quit,true);
}

void USTMenuWidget::InitLevelItems()
{
	const auto STGameInstance = GetSTGameInstance();
	if(!STGameInstance) return;

	checkf(STGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if(!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for(auto LevelData: STGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USTLevelItemWidget>(GetWorld(),LevelItemWidgetClass);
		if(!LevelItemWidget) continue;
		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this,&USTMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}
	if(STGameInstance->GetStartUpLevel().LevelName.IsNone())
	{
		OnLevelSelected(STGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(STGameInstance->GetStartUpLevel());
	}
}

void USTMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto STGameInstance = GetSTGameInstance();
	if(!STGameInstance) return;

	STGameInstance->SetStartUpLevel(Data);

	for(auto LevelItemWidget: LevelItemWidgets)
	{
		if(LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

USTGameInstance* USTMenuWidget::GetSTGameInstance() const
{
	if(!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<USTGameInstance>();
}
