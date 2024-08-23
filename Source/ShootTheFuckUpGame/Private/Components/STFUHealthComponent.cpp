// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTFUHealthComponent::USTFUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

float USTFUHealthComponent::GetHealthPercent()
{
    check(MaxHealth > 0);
    return Health / MaxHealth;
}

void USTFUHealthComponent::GivePickUpTo() 
{
    if (!IsDead() && Health < MaxHealth)
    {
        Health = MaxHealth;
    }

}

void USTFUHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AutoHealHandle(DeltaTime);
}

void USTFUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);
    OnHealthChanged.Broadcast(Health);

    AActor* ComponentOwner = GetOwner();

    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTFUHealthComponent::OnTakeAnyDamage);
}

void USTFUHealthComponent::AutoHealHandle(float DeltaTime)
{
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
                AutoHealOn();
            }
        }
    }
}

void USTFUHealthComponent::AutoHealOn()
{
    if (Health < MaxHealth)
    {
        SetHealth(Health + AutoHealValue);
        OnHealthChanged.Broadcast(Health);
    }
    else
    {
        OnAutoHeal = false;
    }
}

void USTFUHealthComponent::SetHealth(float Value)
{
    Health = FMath::Clamp(Value, 0.f, MaxHealth);
}

void USTFUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Health <= 0.0f || IsDead()) return;

    SetHealth(Health - Damage);
    OnHealthChanged.Broadcast(Health);
    IsTakeDamage = true;

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
