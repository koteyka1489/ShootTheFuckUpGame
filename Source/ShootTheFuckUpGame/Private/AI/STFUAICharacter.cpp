// Shoot The Fuck Up Game. All Rights reserved!!!

#include "AI/STFUAICharacter.h"
#include "AI/STFUAIController.h"
#include "GameFramework\CharacterMovementComponent.h"

ASTFUAICharacter::ASTFUAICharacter(const FObjectInitializer& Objinit) : ASTFUCharacter(Objinit) 
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTFUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate                  = FRotator(0.0f, 0.0f, 200.0f);
    }

}
