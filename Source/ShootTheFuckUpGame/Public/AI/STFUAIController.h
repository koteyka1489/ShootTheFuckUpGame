// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/STFUAIPerceptionComponent.h"
#include "STFUAIController.generated.h"

class USTFUAIPerceptionComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUAIController : public AAIController
{
    GENERATED_BODY()

public:
    ASTFUAIController();
    USTFUAIPerceptionComponent* GetPerceptionComponent() { return AIPerceptionComponent; }

protected:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTFUAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    private:
    AActor* GetFocusOnActor() const;
};
