// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STFUCharacter.generated.h"

class UCameraComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASTFUCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
