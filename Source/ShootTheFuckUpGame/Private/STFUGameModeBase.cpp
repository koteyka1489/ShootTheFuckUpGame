// Shoot The Fuck Up Game. All Rights reserved!!!

#include "STFUGameModeBase.h"
#include "Player\STFUCharacter.h"
#include "Player\STFUPlayerController.h"

ASTFUGameModeBase::ASTFUGameModeBase()
{
    DefaultPawnClass      = ASTFUCharacter::StaticClass();
    PlayerControllerClass = ASTFUPlayerController::StaticClass();
}
