// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASTFUProjectile();

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

   // UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
   // UProjectileMovementComponent* MovementComponent;

   // void SetShotDirection(FVector Direction) { ShotDirection = Direction; }

protected:
    virtual void BeginPlay() override;
   // FVector ShotDirection;
};
