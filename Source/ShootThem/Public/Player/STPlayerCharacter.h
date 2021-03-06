// Shoot Them Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STBaseCharacter.h"
#include "STPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
UCLASS()
class SHOOTTHEM_API ASTPlayerCharacter : public ASTBaseCharacter
{
	GENERATED_BODY()
	ASTPlayerCharacter(const FObjectInitializer& ObjInit);
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	USphereComponent* CameraCollisionComponent;

	virtual void OnDeath() override;
	virtual void BeginPlay() override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

private:
	bool WantsToRun = false;
	bool IsMoveForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRun();
	void OnStopRun();

	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckCameraOverlap();
};
