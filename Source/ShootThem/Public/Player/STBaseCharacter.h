// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "STBaseWeaponActor.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "STBaseCharacter.generated.h"

class USTHealthComponent;
class UTextRenderComponent;
class USTWeaponComponent;
UCLASS()
class SHOOTTHEM_API ASTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	USTHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")//delete this
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	USTWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly,Category="Damage")
	float LifSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly,Category="Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1500.0f);

	UPROPERTY(EditDefaultsOnly,Category="Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly,Category="Material")
	FName MaterialColorName = "Paint Color";

	virtual void BeginPlay() override;
	virtual void OnDeath();
public:
	UFUNCTION(BlueprintCallable,Category="Movement")
	virtual bool IsRunning() const;
	
	UFUNCTION(BlueprintCallable,Category="Movement")
	float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

	virtual void Tick(float DeltaTime) override;
	virtual void OnHealthChanged(float Health,float HealthDelta);
private:
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
