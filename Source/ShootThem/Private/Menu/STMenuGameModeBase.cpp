// Shoot Them Game, All Right Reserved


#include "Menu/STMenuGameModeBase.h"
#include "Menu/STMenuPlayerController.h"
#include "Menu/UI/STMenuHUD.h"
ASTMenuGameModeBase::ASTMenuGameModeBase()
{
	PlayerControllerClass = ASTMenuPlayerController::StaticClass();
	HUDClass = ASTMenuHUD::StaticClass();
}
