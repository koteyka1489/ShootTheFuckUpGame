// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTFUBaseWeapon();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    FColor LineColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Damage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float TimeBetwenShots = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Recoil = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float RecoilStep = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float XRecoil = 40.0f;

    virtual void StartFire();
    virtual void StopFire();

protected:
    virtual void BeginPlay() override;

    void MakeShot();
    ACharacter* GetCharacter();
    APlayerController* GetController();
    void GetTraceStartAndEnd(FVector& TraceStart, FVector& TraceEnd);
    void GetHitResult(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    FTransform GetSocketTranform();

private:
    FTimerHandle TimerHandler;
    void RecoilHandler(FVector& TraceEnd);
};
