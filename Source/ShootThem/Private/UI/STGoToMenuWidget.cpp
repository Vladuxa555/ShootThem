// Shoot Them Game, All Right Reserved


#include "UI/STGoToMenuWidget.h"
#include "Components/Button.h"
#include "STGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTGoToMenu ,All, All);

void USTGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this,&USTGoToMenuWidget::OnGoToMenu);
	}
}

void USTGoToMenuWidget::OnGoToMenu()
{
	if(!GetWorld()) return;

	const auto STGameInstance = GetWorld()->GetGameInstance<USTGameInstance>();
	if(!STGameInstance) return;

	if(STGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogSTGoToMenu,Warning,TEXT("Menu level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(this,STGameInstance->GetMenuLevelName());
	
}
