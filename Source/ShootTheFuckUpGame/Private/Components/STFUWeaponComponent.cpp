// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Components/STFUWeaponComponent.h"
#include "Weapon/STFUBaseWeapon.h"
#include "GameFramework\Character.h"
#include "Animations/STFUEquipFinishedAnimNotify.h"
#include "Animations/STFUReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_WEAPON_COMPOONENT, All, All);

USTFUWeaponComponent::USTFUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTFUWeaponComponent::StartFire()
{
    if (!CurrentWeapon || !CanDoAction()) return;
    CurrentWeapon->StartFire();
}

void USTFUWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTFUWeaponComponent::NextWeapon()
{
    CurrentWeapon->StopFire();
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTFUWeaponComponent::OnClipEmpty() 
{
    Reload();
}

void USTFUWeaponComponent::Reload()
{
    CurrentWeapon->StopFire();
    
    if (!CurrentWeapon->IsNoClips())
    {
        PlayAnimMontage(CurrentReloadAnimMontage);
        ReloadAnimationIsRun = true;
    }
    CurrentWeapon->ChangeClip();
}

void USTFUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Character = Cast<ACharacter>(GetOwner());
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
    InitAnimation();
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

    for (auto& WData : WeaponData)
    {
        auto Weapon            = GetWorld()->SpawnActor<ASTFUBaseWeapon>(WData.WeaponClass);
        auto ReloadAnimMontage = WData.ReloadAnimMontage;
        if (!Weapon) continue;

        Weapon->OnClipEmpty.AddUObject(this, &USTFUWeaponComponent::OnClipEmpty);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        ReloadAnimMontages.Add(ReloadAnimMontage);
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
    if (!GetWorld() || !Character || !CanDoAction()) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    PlayAnimMontage(EquipAnimMonatage);
    EquipAnimationIsRun      = true;
    CurrentWeapon            = Weapons[WeaponIndex];
    CurrentReloadAnimMontage = ReloadAnimMontages[WeaponIndex];

    AtachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEqiupSocketName);
}

void USTFUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    Character->PlayAnimMontage(Animation);
}

void USTFUWeaponComponent::InitAnimation()
{
    if (!EquipAnimMonatage) return;
    const auto EquipNotifyEvents = EquipAnimMonatage->Notifies;
    for (auto NotifyEvent : EquipNotifyEvents)
    {
        auto EquipFinishedNotify = Cast<USTFUEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotifide.AddUObject(this, &USTFUWeaponComponent::OnEquipFinished);
            UE_LOG(LOG_WEAPON_COMPOONENT, Display, TEXT("BIND EquipFinished"));
        }
        else
        {
            UE_LOG(LOG_WEAPON_COMPOONENT, Error, TEXT("Equip anim notify forgoten to set"));
            checkNoEntry();
        }
    }

    if (!CurrentReloadAnimMontage) return;

    for (auto ReloadAnimMontage : ReloadAnimMontages)
    {
        const auto ReloadNotifyEvents = ReloadAnimMontage->Notifies;
        for (auto ReloadNotifyEvent : ReloadNotifyEvents)
        {
            auto ReloadFinishedNotify = Cast<USTFUReloadFinishedAnimNotify>(ReloadNotifyEvent.Notify);
            if (ReloadFinishedNotify)
            {
                ReloadFinishedNotify->OnNotifide.AddUObject(this, &USTFUWeaponComponent::OnReloadFinished);
                UE_LOG(LOG_WEAPON_COMPOONENT, Display, TEXT("BIND ReloadFinished"));
            }
            else
            {
                UE_LOG(LOG_WEAPON_COMPOONENT, Error, TEXT("Reload anim notify forgoten to set"));
                checkNoEntry();
            }
        }
    }
}

void USTFUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    if (Character->GetMesh() == MeshComp)
    {
        EquipAnimationIsRun = false;
        UE_LOG(LOG_WEAPON_COMPOONENT, Display, TEXT("OnEquipFinished"));
    }
}

void USTFUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    if (Character->GetMesh() == MeshComp)
    {
        ReloadAnimationIsRun = false;
        UE_LOG(LOG_WEAPON_COMPOONENT, Display, TEXT("OnReloadFinished"));
    }
}

bool USTFUWeaponComponent::CanDoAction()
{
    return !EquipAnimationIsRun && !ReloadAnimationIsRun;
}
