// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUWeaponComponent.h"
#include "Weapon/STFUBaseWeapon.h"
#include "GameFramework\Character.h"

// Sets default values for this component's properties
USTFUWeaponComponent::USTFUWeaponComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUWeaponComponent::StartFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void USTFUWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTFUWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTFUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTFUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTFUWeaponComponent::SpawnWeapons()
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    for (auto WeaponClass : WeaponClassess)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTFUBaseWeapon>(WeaponClass);
        if (!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AtachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTFUWeaponComponent::AtachWeaponToSocket(ASTFUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTFUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEqiupSocketName);
}
