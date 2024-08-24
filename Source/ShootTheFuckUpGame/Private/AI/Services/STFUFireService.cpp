// Shoot The Fuck Up Game. All Rights reserved!!!


#include "AI/Services/STFUFireService.h"
#include "BehaviorTree\BlackBoardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Components/STFUAIPerceptionComponent.h"
#include "Components\STFUWeaponComponent.h"

USTFUFireService::USTFUFireService() 
{
    NodeName = "Fire Service";
}

void USTFUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    const auto Controller = OwnerComp.GetAIOwner();

    const bool HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->GetComponentByClass<USTFUWeaponComponent>();
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

}
