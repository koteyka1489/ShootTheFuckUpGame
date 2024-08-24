// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STFUAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API USTFUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
	public:
    AActor* GetClosestEnemy();

};
