// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon\STFUBaseWeapon.h"
#include "STFUPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTTHEFUCKUPGAME_API USTFUPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHelthPercent();

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;
};
