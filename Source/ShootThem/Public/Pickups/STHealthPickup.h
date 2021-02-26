// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "Pickups/STBasePickup.h"
#include "STHealthPickup.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTHealthPickup : public ASTBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup",meta = (ClampMin="1.0",ClampMax="100.0"))
	float HealthAmount=100.0f;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
