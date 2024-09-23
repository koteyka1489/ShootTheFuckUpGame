// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STFUBaseWeapon.h"
#include "STFURiffleWeapon.generated.h"

class USTFUWeaponFxComponent;

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
    virtual void BeginPlay() override;
    
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    FColor LineColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Damage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float TimeBetwenShots = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Recoil = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float RecoilStep = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float XRecoil = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    USTFUWeaponFxComponent* WeaponFxComponent;

private:
    FTimerHandle TimerHandler;

    void RecoilHandler(FVector& TraceEnd);
 
};
