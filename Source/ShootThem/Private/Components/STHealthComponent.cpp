// Shoot Them Game, All Right Reserved


#include "Components/STHealthComponent.h"
#include "GameFramework/Actor.h"

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
	Health = MaxHealth;

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
	Health-=Damage;
}
