// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
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

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

protected:
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* EquipAnimMontage;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASTBaseWeaponActor* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTBaseWeaponActor*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage;
	
	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	
	void AttachWeaponToSocket(ASTBaseWeaponActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void SpawnWeapons();
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();


	
};
