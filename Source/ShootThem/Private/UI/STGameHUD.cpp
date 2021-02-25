// Shoot Them Game, All Right Reserved


#include "UI/STGameHUD.h"
#include "Engine/Canvas.h"
void ASTGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
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