// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STFUNextLocationTask.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API USTFUNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    USTFUNextLocationTask();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;
};
