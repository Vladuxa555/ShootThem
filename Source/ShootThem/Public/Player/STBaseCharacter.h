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


class UCameraComponent;
class USpringArmComponent;
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
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	USTHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
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


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool IsRunning() const;
	UFUNCTION(BlueprintCallable,Category="Movement")
	float GetMovementDirection() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	bool WantsToRun = false;
	bool IsMoveForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRun();
	void OnStopRun();

	void OnDeath();
	void OnHealthChanged(float Health,float HealthDelta);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
