// Shoot Them Game, All Right Reserved


#include "Menu/UI/STLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &USTLevelItemWidget::OnLevelItemClicked);
	}
}

void USTLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if(LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}
	if(LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void USTLevelItemWidget::SetSelected(bool IsSelected)
{
	if(FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible :ESlateVisibility::Hidden);
	}
}
void USTLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}
