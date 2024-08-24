// Shoot The Fuck Up Game. All Rights reserved!!!

#include "AI/STFUAIController.h"
#include "AI/STFUAICharacter.h"
#include "BehaviorTree\BlackBoardComponent.h"

ASTFUAIController::ASTFUAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USTFUAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ASTFUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto STFUCharacter = Cast<ASTFUAICharacter>(InPawn);
    if (STFUCharacter)
    {
        RunBehaviorTree(STFUCharacter->BehaviorTreeAsset);
    }
}

void ASTFUAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SetFocus(GetFocusOnActor());
}

AActor* ASTFUAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
