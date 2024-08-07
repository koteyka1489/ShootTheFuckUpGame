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
    TArray<TSubclassOf<ASTFUBaseWeapon>> WeaponClassess;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEqiupSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ASTFUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTFUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0.f;

    void SpawnWeapons();

    void AtachWeaponToSocket(ASTFUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);
};