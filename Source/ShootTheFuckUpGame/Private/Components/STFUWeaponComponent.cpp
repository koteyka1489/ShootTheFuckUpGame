// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUWeaponComponent.h"
#include "Weapon/STFUBaseWeapon.h"
#include "GameFramework\Character.h"

// Sets default values for this component's properties
USTFUWeaponComponent::USTFUWeaponComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUWeaponComponent::Fire()
{
    if (!CurentWeapon) return;
    CurentWeapon->Fire();
}

void USTFUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void USTFUWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    CurentWeapon = GetWorld()->SpawnActor<ASTFUBaseWeapon>(WeaponClass);
    if (!CurentWeapon) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}