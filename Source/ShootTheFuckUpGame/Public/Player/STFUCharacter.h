// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STFUCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASTFUCharacter(const FObjectInitializer& Objinit);

    // Functions
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Variables
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "State")
    bool GetIsRuningAndMoveForward() const { return IsRuning && IsMoveForward; }

    UFUNCTION(BlueprintCallable, Category = "State")
    float GetDotProductForwardVecAndVelocityVec() const;

    UFUNCTION(BlueprintCallable, Category = "State")
    float GetDotProductRightVecAndVelocityVec() const;

private:
    bool IsRuning      = false;
    bool IsMoveForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void RuningOn();
    void RuningOff();
};
