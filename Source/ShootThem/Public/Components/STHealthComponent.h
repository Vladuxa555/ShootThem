// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEM_API USTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTHealthComponent();
	float GetHealth() const {return Health;}

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Health",meta = (ClampMin="0.0",ClampMax="1000"))
	float MaxHealth = 100.0f;
	
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	UFUNCTION()
	void OnTakeAnyDamage (AActor* DamagedActor, float Damage, const class UDamageType*
		DamageType, class AController* InstigatedBy, AActor* DamageCauser );

};
