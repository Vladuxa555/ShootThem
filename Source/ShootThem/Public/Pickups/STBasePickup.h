// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEM_API ASTBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere,Category="Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere,Category="Pickup")
	float RespawnTime = 5.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	private:
	float RotationYaw = 0.0f;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	
	void PickupWasTaken();
	void Respawn();

	void GenerateRotationYaw();
};
