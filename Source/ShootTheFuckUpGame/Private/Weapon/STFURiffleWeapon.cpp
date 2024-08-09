// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Weapon/STFURiffleWeapon.h"
#include "Kismet/GameplayStatics.h"

ASTFURiffleWeapon::ASTFURiffleWeapon() {}

void ASTFURiffleWeapon::StartFire() 
{
    MakeShot();

    GetWorldTimerManager().SetTimer(TimerHandler, this,
        &ASTFURiffleWeapon::MakeShot, TimeBetwenShots, true);
}

void ASTFURiffleWeapon::StopFire() 
{
    GetWorldTimerManager().ClearTimer(TimerHandler);
    Recoil = 0.5f;
}

void ASTFURiffleWeapon::MakeShot() 
{
    BulletsReduction();
    if (!GetWorld() || IsClipEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    GetTraceStartAndEnd(TraceStart, TraceEnd);

    RecoilHandler(TraceEnd);

    FHitResult HitResult;
    GetHitResult(HitResult, TraceStart, TraceEnd);

    float DebugLineLifeTime  = 1.0f;
    float DebugLineThickness = 1.0f;
    uint8 DepthPrioroty      = 0u;
    float SphereRadius       = 10.0f;
    int32 SphereTesselation  = 24;

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetSocketTranform().GetLocation(), HitResult.ImpactPoint, LineColor, false, DebugLineLifeTime,
            DepthPrioroty, DebugLineThickness);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SphereRadius, SphereTesselation, FColor::Cyan, false, DebugLineLifeTime,
            DepthPrioroty, DebugLineThickness);

        UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), Damage, TraceStart, HitResult, nullptr, GetOwner(), nullptr);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetSocketTranform().GetLocation(), TraceEnd, LineColor, false, DebugLineLifeTime, DepthPrioroty,
            DebugLineThickness);
    }
    
}

void ASTFURiffleWeapon::RecoilHandler(FVector& TraceEnd) 
{
    TraceEnd.Z += Recoil;
    Recoil += RecoilStep;
    float RecoilX = FMath::FRandRange(-XRecoil, XRecoil);
    TraceEnd.X += RecoilX;
}


