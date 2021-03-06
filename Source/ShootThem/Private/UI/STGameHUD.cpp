// Shoot Them Game, All Right Reserved


#include "UI/STGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTGameHUD ,All, All);

void ASTGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void ASTGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESTMatchState::InProgress,CreateWidget<UUserWidget>(GetWorld(),PlayerHUDWidgetClass));
	GameWidgets.Add(ESTMatchState::Pause,CreateWidget<UUserWidget>(GetWorld(),PauseWidgetClass));
	GameWidgets.Add(ESTMatchState::GameOver,CreateWidget<UUserWidget>(GetWorld(),GameOverWidgetClass));

	for(auto GameWidgetPair: GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this,&ASTGameHUD::OnMatchStateChanged);
		}
	}
}

void ASTGameHUD::DrawCrossHair()
{
	const TInterval <float>  Center(Canvas->SizeX * 0.5f,Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Green;
	
	DrawLine(Center.Min-HalfLineSize, Center.Max,
		Center.Min + HalfLineSize, Center.Max,LinearColor,LineThickness);
	DrawLine(Center.Min, Center.Max-HalfLineSize,
        Center.Min, Center.Max + HalfLineSize,LinearColor,LineThickness);
}

void ASTGameHUD::OnMatchStateChanged(ESTMatchState State)
{
	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}
	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	UE_LOG(LogSTGameHUD,Display,TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
