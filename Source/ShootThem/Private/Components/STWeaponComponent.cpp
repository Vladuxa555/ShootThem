// Shoot Them Game, All Right Reserved


#include "Components/STWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STBaseWeaponActor.h"

USTWeaponComponent::USTWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void USTWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTWeaponComponent::SpawnWeapon()                                                       
{
	if (!GetWorld()) return;
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTBaseWeaponActor>(WeaponClass);
	if(!CurrentWeapon)return;
	
	FAttachmentTransformRules AttachementRules(EAttachmentRule::SnapToTarget,false);   
	CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachementRules,WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}



void USTWeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USTWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}
