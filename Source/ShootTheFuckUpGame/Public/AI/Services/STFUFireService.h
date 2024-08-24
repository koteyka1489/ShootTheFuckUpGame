// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STFUFireService.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API USTFUFireService : public UBTService
{
    GENERATED_BODY()
public:
    USTFUFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
