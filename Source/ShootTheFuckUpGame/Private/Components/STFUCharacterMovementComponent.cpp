// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Components/STFUCharacterMovementComponent.h"
#include "Player\STFUCharacter.h"

float USTFUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    ASTFUCharacter* Player = Cast<ASTFUCharacter>(GetPawnOwner());

    return Player && Player->GetIsRuningAndMoveForward() ? MaxSpeed * SpeedFactor : MaxSpeed;
}
