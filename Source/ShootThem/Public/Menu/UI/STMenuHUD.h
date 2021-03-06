// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMenuHUD.generated.h"


UCLASS()
class SHOOTTHEM_API ASTMenuHUD : public AHUD
{
	GENERATED_BODY()
	protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category= "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;
};
