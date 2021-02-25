// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STProjectile.h"
#include "Weapon/STBaseWeaponActor.h"
#include "STLauncherWeaponActor.generated.h"

class ASTProjectile;
/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTLauncherWeaponActor : public ASTBaseWeaponActor
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<ASTProjectile> ProjectileClass;
	virtual void MakeShot() override;
};
