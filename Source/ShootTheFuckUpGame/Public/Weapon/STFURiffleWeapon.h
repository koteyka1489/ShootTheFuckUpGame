// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STFUBaseWeapon.h"
#include "STFURiffleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFURiffleWeapon : public ASTFUBaseWeapon
{
    GENERATED_BODY()

public:
    ASTFURiffleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

    protected:
    virtual void MakeShot() override;

    private:
    FTimerHandle TimerHandler;
    void RecoilHandler(FVector& TraceEnd);

};
