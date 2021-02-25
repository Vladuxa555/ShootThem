#pragma once
#include"STCoreTypes.generated.h"
class ASTBaseWeaponActor;
//Weapon
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int32 Bullets;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta = (EditCondition ="!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()
	
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<ASTBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	UAnimMontage* ReloadAnimMontage;
};

//Health
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float)