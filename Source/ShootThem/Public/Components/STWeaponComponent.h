// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STWeaponComponent.generated.h"

class ASTBaseWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEM_API USTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTWeaponComponent();

	void StartFire();
	void StopFire();

protected:
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<ASTBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTBaseWeaponActor* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
