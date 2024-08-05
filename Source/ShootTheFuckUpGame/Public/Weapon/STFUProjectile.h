// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASTFUProjectile();

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

protected:
    virtual void BeginPlay() override;
};
