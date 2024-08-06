// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUProjectile.h"
#include "Components\SphereComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"

ASTFUProjectile::ASTFUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    //MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void ASTFUProjectile::BeginPlay()
{
    Super::BeginPlay();

    //MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
}
