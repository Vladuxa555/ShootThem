// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STBaseWeaponActor.h"
#include "STRifleWeaponActor.generated.h"

class USTWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class SHOOTTHEM_API ASTRifleWeaponActor : public ASTBaseWeaponActor
{
	GENERATED_BODY()
	public:
	ASTRifleWeaponActor();
	virtual void StartFire()override;
	virtual void StopFire()override;
	
	protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	float TimeBetweenShots = 0.1f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	float BulletSpred = 1.5f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	FString TraceTargetName = "TraceTarget";

	UPROPERTY(VisibleAnywhere,Category="VFX")
	USTWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	
	private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFxComponent;
	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleEffectVisibility(bool Visible);
	void SpawnTrace(const FVector& TraceStart,const FVector& TraceEnd);
};
