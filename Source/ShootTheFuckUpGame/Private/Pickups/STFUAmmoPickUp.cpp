// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Pickups/STFUAmmoPickUp.h"
#include "Player\STFUCharacter.h"

bool ASTFUAmmoPickUp::GivePickUpTo(APawn* Pawn)
{
    auto Player = Cast<ASTFUCharacter>(Pawn);
    if (Player)
    {
        Player->GivePickUpTo(this);
        return true;
    }
    else
    {
        return false;
    }
}
