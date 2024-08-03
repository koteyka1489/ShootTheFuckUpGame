// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STFUWeaponComponent.generated.h"

class ASTFUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEFUCKUPGAME_API USTFUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTFUWeaponComponent();

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASTFUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponSocket";

    void StartFire();
    void StopFire();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ASTFUBaseWeapon* CurentWeapon = nullptr;

    void SpawnWeapon();
};