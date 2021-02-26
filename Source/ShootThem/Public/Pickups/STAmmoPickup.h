// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STBasePickup.h"
#include "STAmmoPickup.generated.h"

class ASTBaseWeaponActor;

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTAmmoPickup : public ASTBasePickup
{
	GENERATED_BODY()
	protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup",meta = (ClampMin="1.0",ClampMax="10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	TSubclassOf<ASTBaseWeaponActor> WeaponType;
	
	private:
	virtual bool GivePickupTo(APawn* PlayerPawn)override;
};
