// Shoot Them Game, All Right Reserved


#include "Pickups/STBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup,All,All);

// Sets default values
ASTBasePickup::ASTBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
	bReplicates =true;
}

// Called when the game starts or when spawned
void ASTBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
	GenerateRotationYaw();
}

void ASTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if(GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

// Called every frame
void ASTBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f,RotationYaw,0.0f));

}

bool ASTBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false,true);
	}
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle,this,&ASTBasePickup::Respawn,RespawnTime);
}

void ASTBasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true,true);
	}
}

void ASTBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool()? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f,2.0f)* Direction;
}

