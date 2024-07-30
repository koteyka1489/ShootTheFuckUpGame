// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTFUHealthComponent::USTFUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

    AActor* ComponentOwner = GetOwner();

    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTFUHealthComponent::OnTakeAnyDamage);
}

void USTFUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Health <= 0.0f || IsDead()) return;

    Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
