// Shoot Them Game, All Right Reserved


#include "Weapon/STBaseWeaponActor.h"

#include <destructible/ModuleDestructible.h>

#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All);

ASTBaseWeaponActor::ASTBaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void ASTBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh)
}

void ASTBaseWeaponActor::MakeShot()
{

}

APlayerController* ASTBaseWeaponActor::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTBaseWeaponActor::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) return false;
	
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);
	return true;
}

FVector ASTBaseWeaponActor::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTBaseWeaponActor::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const FVector ShootDirection = (ViewRotation.Vector());
	TraceEnd = TraceStart + ShootDirection*TraceMaxDistance;
	return true;
}

void ASTBaseWeaponActor::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetNetOwner());
	
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility,CollisionParams);

}

void ASTBaseWeaponActor::StartFire()
{
	
}

void ASTBaseWeaponActor::StopFire()
{
	
}


