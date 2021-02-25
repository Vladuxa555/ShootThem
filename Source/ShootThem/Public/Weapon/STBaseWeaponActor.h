// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STCoreTypes.h"
#include "STBaseWeaponActor.generated.h"



class USkeletalMeshComponent;

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

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FAmmoData DefaultAmmo{15,10,false};
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

	virtual void MakeShot();
	APlayerController* GetPlayerController() const;
	
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsAmmoEmpty()const;
	bool IsClipEmpty()const;
	void LogAmmo();
	private:
	FAmmoData CurrentAmmo;
};
