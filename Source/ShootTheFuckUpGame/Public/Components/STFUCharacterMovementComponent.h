// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STFUCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API USTFUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta =(ClampMin = "1.5", ClampMax = "10.0"))
    float SpeedFactor = 2.0f;
};
