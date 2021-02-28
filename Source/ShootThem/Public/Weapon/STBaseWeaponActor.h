// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STCoreTypes.h"
#include "STBaseWeaponActor.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
UCLASS()
class SHOOTTHEM_API ASTBaseWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTBaseWeaponActor();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();
	void ChangeClip();
	bool CanReload();

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="UI")
	FWeaponUIData UIData;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	UNiagaraSystem* MuzzleFX;
	virtual void BeginPlay() override;

	virtual void MakeShot();
	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool IsAmmoFull() const;

	void LogAmmo();

	UNiagaraComponent* SpawnMuzzleFX();
private:
	FAmmoData CurrentAmmo;
};
