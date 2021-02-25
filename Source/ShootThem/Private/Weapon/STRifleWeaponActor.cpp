// Shoot Them Game, All Right Reserved


#include "Weapon/STRifleWeaponActor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon,All,All);

void ASTRifleWeaponActor::MakeShot()
{
	if(!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart,TraceEnd;
	if(!GetTraceData(TraceStart,TraceEnd))
	{
		StopFire();
		return;
	}
	
	FHitResult HitResult;
	MakeHit(HitResult,TraceStart,TraceEnd);

	if(HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(),GetMuzzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,
            false,3.0f,0,3.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,24,FColor::Red,false,5.0f);
		UE_LOG(LogRifleWeapon,Display,TEXT("Bone: %s"),*HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(),GetMuzzleWorldLocation(),TraceEnd,
            FColor::Red,false,3.0f,0,3.0f);
	}
	DecreaseAmmo();
}

void ASTRifleWeaponActor::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ASTRifleWeaponActor::MakeShot,TimeBetweenShots,true);
	MakeShot();
}

void ASTRifleWeaponActor::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

bool ASTRifleWeaponActor::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpred);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(),HalfRad);
	TraceEnd = TraceStart + ShootDirection*TraceMaxDistance;
	return true;
}

void ASTRifleWeaponActor::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount,FDamageEvent(),GetPlayerController(),this);
}