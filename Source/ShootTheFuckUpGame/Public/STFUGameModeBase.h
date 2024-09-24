// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STFUGameModeBase.generated.h"

class AAIController;

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayerNum = 4;
};

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTFUGameModeBase();
    virtual void StartPlay() override;

    
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawn;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    void SpawnBots();
};
