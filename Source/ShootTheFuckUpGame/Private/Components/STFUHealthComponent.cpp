// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev\STFUFireDamageType.h"
#include "Dev\STFUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

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
    UE_LOG(LogHealthComponent, Display, TEXT("Damage - %f"), Damage)

    if (DamageType)
    {
        if (DamageType->IsA<USTFUFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("DamageType Fire"))
        }
        if (DamageType->IsA<USTFUIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("DamageType Ice"))
        }
    }
}
