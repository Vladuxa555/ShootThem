// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STBaseWeaponActor.generated.h"

class USkeletalMeshComponent;
UCLASS()
class SHOOTTHEM_API ASTBaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTBaseWeaponActor();

	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	APlayerController *GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart,FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd);

};
