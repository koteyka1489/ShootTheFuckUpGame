// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STFUGameHUD.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
