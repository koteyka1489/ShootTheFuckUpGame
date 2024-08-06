// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_PROJECTILE, All, All);

ASTFUProjectile::ASTFUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 3.0f;
}

void ASTFUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

    SetLifeSpan(5.0f);
}
