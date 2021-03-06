// Shoot Them Game, All Right Reserved


#include "Player/STPlayerController.h"
#include "Components/STRespawnComponent.h"
#include "STGameModeBase.h"

ASTPlayerController::ASTPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTRespawnComponent>("RespawnComponent");
}

void ASTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		const auto GameMode = Cast<ASTGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this,&ASTPlayerController::OnMatchStateChanged);
		}
	}
}

void ASTPlayerController::OnMatchStateChanged(ESTMatchState State)
{
	if(State == ESTMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	
}

void ASTPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void ASTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame",IE_Pressed,this,&ASTPlayerController::OnPauseGame);
}

void ASTPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->SetPause(this);
}
