// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUBaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool Infinite = false;
};

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTFUBaseWeapon();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{30, 5, false};

    virtual void StartFire();
    virtual void StopFire();

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual void GetTraceStartAndEnd(FVector& TraceStart, FVector& TraceEnd);

    ACharacter* GetCharacter();
    APlayerController* GetController();

    void GetHitResult(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    FTransform GetSocketTranform();
    FVector GetSocketWorldLocation();

    bool IsBulletsEmpty();
    bool IsAmmoEmpty();
    bool IsClipsEmpty();
    void BulletsReduction();
    void Reloading();

private:
    FAmmoData CurrentAmmo;
};
