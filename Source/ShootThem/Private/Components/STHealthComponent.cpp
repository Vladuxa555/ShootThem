// Shoot Them Game, All Right Reserved


#include "Components/STHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All)

// Sets default values for this component's properties
USTHealthComponent::USTHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);

	// ...
	AActor *ComponentOwner = GetOwner();
	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this,&USTHealthComponent::OnTakeAnyDamage);
	}
	
}

void USTHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || IsDead() || !GetWorld()) return;
	
	SetHealth(Health-Damage);
	
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USTHealthComponent::HealUpdate,HealUpdateTime,true,HealDelay);
	}
}

void USTHealthComponent::HealUpdate()
{
	SetHealth(Health+HealModifier);

	if(FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
