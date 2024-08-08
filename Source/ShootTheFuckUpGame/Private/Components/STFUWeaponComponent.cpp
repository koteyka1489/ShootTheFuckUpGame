// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUWeaponComponent.h"
#include "Weapon/STFUBaseWeapon.h"
#include "GameFramework\Character.h"
#include "Animations/STFUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_WEAPON_COMPOONENT, All, All);


USTFUWeaponComponent::USTFUWeaponComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUWeaponComponent::StartFire()
{
    if (!CurrentWeapon || !CanFire()) return;
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
    InitAnimation(); 
    Character = Cast<ACharacter>(GetOwner());
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
    if (!GetWorld() || !Character) return;

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
    if (!GetWorld() || !Character || !CanEquip()) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    PlayAnimMontage(EquipAnimMonatage);
    EquipAnimationIsRun = true;
    CurrentWeapon = Weapons[WeaponIndex];
    AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEqiupSocketName);
}

void USTFUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    Character->PlayAnimMontage(Animation);
}

void USTFUWeaponComponent::InitAnimation() 
{
    if (!EquipAnimMonatage) return;
    const auto NotifyEvents = EquipAnimMonatage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<USTFUEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotifide.AddUObject(this, &USTFUWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void USTFUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{

    if (Character->GetMesh() == MeshComp)
    {
        EquipAnimationIsRun = false;
    }
    
}

bool USTFUWeaponComponent::CanFire()
{
    return !EquipAnimationIsRun;
}

bool USTFUWeaponComponent::CanEquip()
{
    return !EquipAnimationIsRun;
}
