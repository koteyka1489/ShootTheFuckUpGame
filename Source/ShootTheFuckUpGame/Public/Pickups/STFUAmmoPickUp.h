// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STFUBasePickUp.h"
#include "STFUAmmoPickUp.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUAmmoPickUp : public ASTFUBasePickUp
{
    GENERATED_BODY()

protected:
    virtual bool GivePickUpTo(APawn* Pawn) override;
};
