// Shoot The Fuck Up Game. All Rights reserved!!!


#include "AI/Tasks/STFUNextLocationTask.h"
#include "BehaviorTree\BlackBoardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"

USTFUNextLocationTask::USTFUNextLocationTask() 
{
    NodeName = "Next Location";
}

EBTNodeResult::Type USTFUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !BlackBoard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    bool NavResult = NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
    if (!NavResult) return EBTNodeResult::Failed;

    BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Succeeded;
}
