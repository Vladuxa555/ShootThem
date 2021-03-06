// Shoot Them Game, All Right Reserved


#include "Menu/STMenuPlayerController.h"
#include "STGameInstance.h"

void ASTMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}
