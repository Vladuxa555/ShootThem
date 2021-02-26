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
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets>0 ,TEXT("Bullets count couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips>0,TEXT("Clips count couldn't be less or equal zero"));
	CurrentAmmo = DefaultAmmo;
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

void ASTBaseWeaponActor::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets==0)
	{
		UE_LOG(LogBaseWeapon,Warning,TEXT("Climp Is Empty"));
		return;
	}
	CurrentAmmo.Bullets--;

	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool ASTBaseWeaponActor::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTBaseWeaponActor::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void ASTBaseWeaponActor::ChangeClip() 
{
	
	if(!CurrentAmmo.Infinite)
	{
		if(CurrentAmmo.Clips==0)
		{
			UE_LOG(LogBaseWeapon,Warning,TEXT("No More Clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogBaseWeapon,Display,TEXT("--------------Change Clip---------------"));
}

bool ASTBaseWeaponActor::CanReload()
{
	return CurrentAmmo.Bullets <DefaultAmmo.Bullets && CurrentAmmo.Clips>0;
}

void ASTBaseWeaponActor::LogAmmo() 
{
	FString AmmoInfo = "Ammo" + FString::FromInt(CurrentAmmo.Bullets)+"/";
	AmmoInfo +=CurrentAmmo.Infinite? "Infinite":FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon,Display,TEXT("%s"),*AmmoInfo);
}

void ASTBaseWeaponActor::StartFire()
{
}

void ASTBaseWeaponActor::StopFire()
{
}


