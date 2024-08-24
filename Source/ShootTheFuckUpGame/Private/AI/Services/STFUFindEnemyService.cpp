// Shoot The Fuck Up Game. All Rights reserved!!!

#include "AI/Services/STFUFindEnemyService.h"
#include "BehaviorTree\BlackBoardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Components/STFUAIPerceptionComponent.h"

USTFUFindEnemyService::USTFUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTFUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller          = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Cast<USTFUAIPerceptionComponent>(Controller->GetPerceptionComponent());
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
