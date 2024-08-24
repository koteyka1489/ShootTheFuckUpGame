// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Player/STFUCharacter.h"
#include "STFUAICharacter.generated.h"


class UBehaviorTree;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUAICharacter : public ASTFUCharacter
{
	GENERATED_BODY()
	
	public:
    ASTFUAICharacter(const FObjectInitializer& Objinit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;
};
