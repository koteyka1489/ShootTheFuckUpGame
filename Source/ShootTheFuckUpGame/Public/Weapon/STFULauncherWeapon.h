// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STFUBaseWeapon.h"
#include "STFULauncherWeapon.generated.h"

class ASTFUProjectile;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFULauncherWeapon : public ASTFUBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTFUProjectile> ProjectileClass;

    virtual void MakeShot() override;

};
