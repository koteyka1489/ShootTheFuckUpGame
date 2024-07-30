// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    ASTFUDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEV")
    float Radius = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEV")
    FColor Color = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEV")
    float Damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEV")
    bool DoFullDamage = false;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
