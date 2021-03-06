// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STBaseWeaponActor.h"
#include "STCoreTypes.h"
#include "Components/ActorComponent.h"
#include "STWeaponComponent.generated.h"


class ASTBaseWeaponActor;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEM_API USTWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTWeaponComponent();
	
	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUiData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTBaseWeaponActor> WeaponType,int32 ClipsAmount);

protected:
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* EquipAnimMontage;
	
	UPROPERTY()
	ASTBaseWeaponActor* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTBaseWeaponActor*> Weapons;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);
	int32 CurrentWeaponIndex = 0;
private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	
	void AttachWeaponToSocket(ASTBaseWeaponActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void SpawnWeapons();

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnEmptyClip(ASTBaseWeaponActor* AmmoEmptyWeapon);
	void ChangeClip();


	
};
