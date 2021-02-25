// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTGameHUD : public AHUD
{
	GENERATED_BODY()
	public:
	virtual void DrawHUD() override;

	private:
	void DrawCrossHair();
};