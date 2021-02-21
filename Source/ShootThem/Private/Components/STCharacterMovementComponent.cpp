// Shoot Them Game, All Right Reserved


#include "Components/STCharacterMovementComponent.h"
#include "Player/STBaseCharacter.h"

float USTCharacterMovementComponent::GetMaxSpeed()const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASTBaseCharacter *Player=Cast<ASTBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}