// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STFUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

    UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class SHOOTTHEFUCKUPGAME_API USTFUHealthComponent
    : public UActorComponent
{
    GENERATED_BODY()

public:
    USTFUHealthComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable)
    bool IsDead() { return Health <= 0.0f; }

    UFUNCTION(BlueprintCallable)
    float GetHealthPercent();

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

    void GivePickUpTo();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "1000.0"));
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool IsAutoHealEnabled = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "IsAutoHealEnabled"))
    float AutoHealDelay = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "IsAutoHealEnabled"))
    float AutoHealTick = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "IsAutoHealEnabled"))
    float AutoHealValue = 1.0f;

    virtual void BeginPlay() override;

private:
    float Health              = 0.0f;
    float AutoHealEnebleTimer = 0.0f;
    float AutoHealTickTimer   = 0.0f;
    bool IsTakeDamage         = false;
    bool OnAutoHeal           = false;

    void AutoHealHandle(float DeltaTime);
    void AutoHealOn();
    void SetHealth(float Value);

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
