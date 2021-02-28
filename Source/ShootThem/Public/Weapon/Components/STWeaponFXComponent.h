// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STCoreTypes.h"
#include "STWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEM_API USTWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	FImpactData DefaultImpactData;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};