// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Weapon/STFULauncherWeapon.h"
#include "Weapon\STFUProjectile.h"
#include "Kismet\GameplayStatics.h"


void ASTFULauncherWeapon::StartFire() 
{
    MakeShot();
}

void ASTFULauncherWeapon::MakeShot() 
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetSocketWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
