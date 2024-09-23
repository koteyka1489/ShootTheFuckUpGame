// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STFUWeaponFxComponent.generated.h"

class UNiagaraSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEFUCKUPGAME_API USTFUWeaponFxComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTFUWeaponFxComponent();

    void PlayImpactFX(const FHitResult& Hit);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* Effect;
};
