// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Pickups/STFUHealthPickUp.h"
#include "Player\STFUCharacter.h"

bool ASTFUHealthPickUp::GivePickUpTo(APawn* Pawn)
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
