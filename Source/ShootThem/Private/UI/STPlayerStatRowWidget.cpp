// Shoot Them Game, All Right Reserved


#include "UI/STPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void USTPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void USTPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void USTPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
