// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "STProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEM_API ASTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTProjectile();
	void SetShotDirection(const FVector& Direction){ShotDirection = Direction;}

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere,Category="Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	float DamageRadius = 200.f;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	float LifeSeconds = 5.0f;
private:
	FVector ShotDirection;
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	AController* GetController() const;

};
