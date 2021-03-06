// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;
};
