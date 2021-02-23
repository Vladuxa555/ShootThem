// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
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
UCLASS()
class SHOOTTHEM_API ASTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USpringArmComponent *SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UCameraComponent *CameraComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	USTHealthComponent *HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UTextRenderComponent *HealthTextComponent;

	UPROPERTY(EditDefaultsOnly,Category="Animation")
	UAnimMontage *DeathAnimMontage;
	
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
	bool WantsToRun=false;
	bool IsMoveForward=false;
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	
	void OnStartRun();
	void OnStopRun();

	void OnDeath();
	void OnHealthChanged(float Health);
	
};
