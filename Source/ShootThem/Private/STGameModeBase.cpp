// Shoot Them Game, All Right Reserved


#include "STGameModeBase.h"
#include "Player/STPlayerController.h"
#include "Player/STBaseCharacter.h"
#include "UI/STGameHUD.h"

ASTGameModeBase::ASTGameModeBase()
{
	DefaultPawnClass=ASTBaseCharacter::StaticClass();
	PlayerControllerClass=ASTPlayerController::StaticClass();
	HUDClass=ASTGameHUD::StaticClass();
}

