// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pickups\STFUBasePickUp.h"
#include "STFUCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTFUHealthComponent;
class UTextRenderComponent;
class USTFUWeaponComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTFUCharacter(const FObjectInitializer& Objinit);
    
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "State")
    bool GetIsRuningAndMoveForward() const { return IsRuning && IsMoveForward; }

    UFUNCTION(BlueprintCallable, Category = "State")
    float GetDotProductForwardVecAndVelocityVec() const;

    UFUNCTION(BlueprintCallable, Category = "State")
    float GetDotProductRightVecAndVelocityVec() const;

    bool GivePickUpTo(ASTFUBasePickUp* PickUp);

   

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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTFUWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D FallDamageVelocityMinMax = {900.0f, 1200.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D FallDamageMinMax = {10.0f, 100.0f};

private:
    bool IsRuning      = false;
    bool IsMoveForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void RuningOn();
    void RuningOff();

    void OnDeath();
    void OnHealtChange(float Health);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
