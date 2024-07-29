// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUHealthComponent.h"

// Sets default values for this component's properties
USTFUHealthComponent::USTFUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}
