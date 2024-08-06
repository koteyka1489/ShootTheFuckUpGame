// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Weapon/STFULauncherWeapon.h"
#include "Weapon\STFUProjectile.h"

DEFINE_LOG_CATEGORY_STATIC(LogLauncher, All, All);


void ASTFULauncherWeapon::StartFire() 
{
    MakeShot();
}

void ASTFULauncherWeapon::MakeShot() 
{
    if (!GetWorld()) return;

    FVector TraceStart;
    FVector TraceEnd;
    GetTraceStartAndEnd(TraceStart, TraceEnd);

    FHitResult HitResult;
    GetHitResult(HitResult, TraceStart, TraceEnd);

    FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    FVector Direction = (EndPoint - GetSocketWorldLocation());

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetSocketWorldLocation());
    ASTFUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTFUProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {

        Projectile->SetShotDirection(Direction);
        Projectile->FinishSpawning(SpawnTransform);
    }
}
