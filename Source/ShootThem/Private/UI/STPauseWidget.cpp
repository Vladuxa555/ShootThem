// Shoot Them Game, All Right Reserved


#include "UI/STPauseWidget.h"
#include "STGameModeBase.h"
#include "Components/Button.h"

void USTPauseWidget::NativeOnInitialized()
{
	const auto InitStatus = Super::Initialize();

	if(ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTPauseWidget::OnClearPause);
	}
}

void USTPauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
