// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API USTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Movement",meta = (ClampMin="1.5",ClampMax="10"))
	float RunModifier = 2.0f;
	virtual float GetMaxSpeed() const override;
};
