// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/Components/STFUWeaponFxComponent.h"
#include "NiagaraFunctionLibrary.h"

USTFUWeaponFxComponent::USTFUWeaponFxComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUWeaponFxComponent::PlayImpactFX(const FHitResult& Hit) 
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
