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

};
