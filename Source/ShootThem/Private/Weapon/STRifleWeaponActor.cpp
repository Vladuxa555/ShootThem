// Shoot Them Game, All Right Reserved


#include "Weapon/STRifleWeaponActor.h"

#include <tuple>

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogRifleWeapon,All,All);

ASTRifleWeaponActor::ASTRifleWeaponActor()
{
	WeaponFXComponent = CreateDefaultSubobject<USTWeaponFXComponent>("WeaponFXComponent");
	bReplicates = true;
}

void ASTRifleWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

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

	
	FVector TraceFXEnd = TraceEnd;
	
	if(HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTrace(GetMuzzleWorldLocation(),TraceFXEnd);
	DecreaseAmmo();
}
void ASTRifleWeaponActor::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ASTRifleWeaponActor::MakeShot,TimeBetweenShots,true);
	MakeShot();
}

void ASTRifleWeaponActor::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleEffectVisibility(false);
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

	DamagedActor->TakeDamage(DamageAmount,FDamageEvent(),GetController(),this);
}

void ASTRifleWeaponActor::InitMuzzleFX()
{
	if(!MuzzleFxComponent)
	{
		MuzzleFxComponent = SpawnMuzzleFX();
	}
	SetMuzzleEffectVisibility(true);
}

void ASTRifleWeaponActor::SetMuzzleEffectVisibility(bool Visible)
{
	if(MuzzleFxComponent)
	{
		MuzzleFxComponent->SetPaused(!Visible);
		MuzzleFxComponent ->SetVisibility(Visible,true);
	}
}


void ASTRifleWeaponActor::SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFxComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),TraceFX,TraceStart);
	if(TraceFxComponent)
	{
		TraceFxComponent->SetNiagaraVariableVec3(TraceTargetName,TraceEnd);
	}
}

AController* ASTRifleWeaponActor::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController(): nullptr;
}