// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STFUCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTFUHealthComponent;
class UTextRenderComponent;


UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTFUCharacter(const FObjectInitializer& Objinit);

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTFUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextHealthComponent;

public:
    virtual void Tick(float DeltaTime) override;

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
