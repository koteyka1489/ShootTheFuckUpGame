// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUProjectile.h"
#include "Components\SphereComponent.h"

ASTFUProjectile::ASTFUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);
}

void ASTFUProjectile::BeginPlay()
{
    Super::BeginPlay();

}
