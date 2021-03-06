// Shoot Them Game, All Right Reserved


#include "Player/STBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STCharacterMovementComponent.h"
#include "Components/STHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STWeaponComponent.h"
DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog,All,All);

// Sets default values
ASTBaseCharacter::ASTBaseCharacter(const FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<USTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTHealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USTWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTBaseCharacter::OnGroundLanded);
}
float ASTBaseCharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero())return 0.0f;
	const auto VelocityNormal= GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees*FMath::Sign(CrossProduct.Z);
}

void ASTBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if(!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName,Color);
}

// Called every frame
void ASTBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ASTBaseCharacter::OnDeath()
{
	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifSpanOnDeath);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTBaseCharacter::OnHealthChanged(float Health,float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),Health)));
}

void ASTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(BaseCharacterLog,Display,TEXT("On Landed: %f"), FallVelocityZ);

	if(FallVelocityZ < LandedDamageVelocity.X)return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

	UE_LOG(BaseCharacterLog,Display,TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage,FDamageEvent{},nullptr,nullptr);
}
bool ASTBaseCharacter::IsRunning() const
{
	return false;
}