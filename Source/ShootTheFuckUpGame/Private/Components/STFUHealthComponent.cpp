// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTFUHealthComponent::USTFUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USTFUHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (IsAutoHealEnabled)
    {
        if (IsTakeDamage)
        {
            AutoHealEnebleTimer += DeltaTime;
            if (AutoHealEnebleTimer >= AutoHealDelay)
            {
                AutoHealEnebleTimer = 0.0f;
                IsTakeDamage        = false;
                OnAutoHeal          = true;
            }
        }

        if (OnAutoHeal && !IsTakeDamage && Health < MaxHealth)
        {
            AutoHealTickTimer += DeltaTime;
            if (AutoHealTickTimer >= AutoHealTick)
            {
                AutoHealTickTimer = 0.0f;
                AutoHeal();
            }
        }
    }
}

void USTFUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

    AActor* ComponentOwner = GetOwner();

    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTFUHealthComponent::OnTakeAnyDamage);
}

void USTFUHealthComponent::AutoHeal()
{
    if (Health < MaxHealth)
    {
        Health = FMath::Clamp(Health + AutoHealValue, 0.f, MaxHealth);
        OnHealthChanged.Broadcast(Health);
    }
    else
    {
        OnAutoHeal = false;
    }
}

void USTFUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Health <= 0.0f || IsDead()) return;

    Health       = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
    IsTakeDamage = true;
    

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
