// Shoot Them Game, All Right Reserved


#include "STFireService.h"
#include "Components/STWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUtils.h"

USTFireService::USTFireService()
{
	NodeName = "Fire";
}

void USTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{
		const auto WeaponComponent = STUtils::GetSTPlayerComponent<USTWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent)
		{
			HasAim ?WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
}
