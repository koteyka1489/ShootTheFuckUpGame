// Shoot The Fuck Up Game. All Rights reserved!!!

#include "UI/STFUPlayerHUDWidget.h"
#include "Components\STFUHealthComponent.h"
#include "Components\STFUWeaponComponent.h"



float USTFUPlayerHUDWidget::GetHelthPercent()
{
    const auto HealthComponent = GetPLayerHealthConponent();
    if (!HealthComponent) return 0.0f;
    return HealthComponent->GetHealthPercent();
}

bool USTFUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = GetPLayerWeaponConponent();
    if (!WeaponComponent) return false;
    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTFUPlayerHUDWidget::GetCurrenAmmo(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = GetPLayerWeaponConponent();
    if (!WeaponComponent) return false;
    return WeaponComponent->GetCurrenAmmo(AmmoData);
}

FString USTFUPlayerHUDWidget::GetCurrentAmmoText(FAmmoData& AmmoData)
{
    GetCurrenAmmo(AmmoData);

    if (AmmoData.Infinite)
    {
        return FString::Printf(TEXT(" %i / X "), AmmoData.Bullets);
    }
    else
    {
        return FString::Printf(TEXT(" %i / %i"), AmmoData.Bullets, AmmoData.Clips);
    }
}

bool USTFUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetPLayerHealthConponent();
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTFUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

USTFUWeaponComponent* USTFUPlayerHUDWidget::GetPLayerWeaponConponent() const
{
    auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    auto Component       = Player->GetComponentByClass(USTFUWeaponComponent::StaticClass());
    auto WeaponComponent = Cast<USTFUWeaponComponent>(Component);
    return WeaponComponent;
}

USTFUHealthComponent* USTFUPlayerHUDWidget::GetPLayerHealthConponent() const
{
    auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    auto Component       = Player->GetComponentByClass(USTFUHealthComponent::StaticClass());
    auto HealthComponent = Cast<USTFUHealthComponent>(Component);
    return HealthComponent;
}
