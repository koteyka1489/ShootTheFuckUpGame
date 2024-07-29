// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USTFUHealthComponent::USTFUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();

    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTFUHealthComponent::OnTakeAnyDamage);
}

void USTFUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
}
