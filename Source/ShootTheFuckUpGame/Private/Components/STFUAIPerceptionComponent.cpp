// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AI/STFUAIController.h"
#include "AI/STFUAICharacter.h"
#include "Player/STFUCharacter.h"

class ASTFUAICharacter;

AActor* USTFUAIPerceptionComponent::GetClosestEnemy()
{
    TArray<AActor*> VisibleActors;

    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), VisibleActors);
    if (VisibleActors.Num() == 0) return nullptr;

    const auto Controller = Cast<ASTFUAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto AiPawn = Cast<ASTFUAICharacter>(Controller->GetPawn());
    if (!AiPawn) return nullptr;

    float ClosestDistance = MAX_FLT;
    AActor* ClosestActor  = nullptr;

    for (const auto VisibleActor : VisibleActors)
    {
        const auto Character = Cast<ASTFUCharacter>(VisibleActor);
        if (!Character) return nullptr;
        if (Character->IsAlive())
        {
            FVector VecToActor = VisibleActor->GetActorLocation() - AiPawn->GetActorLocation();
            float Distance     = VecToActor.Length();

            if (!ClosestActor)
            {
                ClosestActor    = VisibleActor;
                ClosestDistance = Distance;
            }
            else
            {
                if (Distance < ClosestDistance)
                {
                    ClosestActor    = VisibleActor;
                    ClosestDistance = Distance;
                }
            }
        }
    }

    return ClosestActor;
}
