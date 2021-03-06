// Shoot Them Game, All Right Reserved


#include "Menu/UI/STMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(),MenuWidgetClass);
		if(MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
