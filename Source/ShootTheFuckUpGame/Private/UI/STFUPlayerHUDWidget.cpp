// Shoot The Fuck Up Game. All Rights reserved!!!

#include "UI/STFUPlayerHUDWidget.h"
#include "Components\STFUHealthComponent.h"
#include "Components\STFUWeaponComponent.h"

float USTFUPlayerHUDWidget::GetHelthPercent()
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component       = Player->GetComponentByClass(USTFUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USTFUHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTFUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto Component       = Player->GetComponentByClass(USTFUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USTFUWeaponComponent>(Component);
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}
