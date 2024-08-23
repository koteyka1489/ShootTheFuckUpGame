// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUBasePickUp : public AActor
{
    GENERATED_BODY()

public:
    ASTFUBasePickUp();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Collision")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Collision")
    float RespawnTime = 5.0f;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual bool GivePickUpTo(APawn* Pawn);

public:
    virtual void Tick(float DeltaTime) override;

private:
    void PickupWasTaken();
    void Respawn();
    void GenerateRoration();

    float RotationPitch = 0.0f;
    float RotationYaw = 0.0f;
    float RotationRoll = 0.0f;
};
