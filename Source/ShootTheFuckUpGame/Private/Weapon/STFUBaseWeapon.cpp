// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUBaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework\Character.h"
#include "GameFramework\Controller.h"
#include "Player\STFUCharacter.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTFUBaseWeapon::ASTFUBaseWeapon()
{

    PrimaryActorTick.bCanEverTick = false;

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    SetRootComponent(SkeletalMeshComponent);
}

void ASTFUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(SkeletalMeshComponent);
}

void ASTFUBaseWeapon::StartFire()
{
    MakeShot();

    GetWorldTimerManager().SetTimer(TimerHandler, this, &ASTFUBaseWeapon::MakeShot, TimeBetwenShots, true);
}

void ASTFUBaseWeapon::StopFire() 
{
    GetWorldTimerManager().ClearTimer(TimerHandler);
    Recoil = 0.5f;
}

void ASTFUBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;
  
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

ACharacter* ASTFUBaseWeapon::GetCharacter()
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;
    return Player;
}

APlayerController* ASTFUBaseWeapon::GetController()
{
    const auto Controller = GetCharacter()->GetController<APlayerController>();
    if (!Controller) return nullptr;
    return Controller;
}

void ASTFUBaseWeapon::GetTraceStartAndEnd(FVector& TraceStart, FVector& TraceEnd)
{
    FVector ViewLocation;
    FRotator ViewRotation;
    GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

    TraceStart                   = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd                     = TraceStart + ShootDirection * TraceMaxDistance;
}

void ASTFUBaseWeapon::GetHitResult(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FTransform ASTFUBaseWeapon::GetSocketTranform()
{
    return SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);
}

void ASTFUBaseWeapon::RecoilHandler(FVector& TraceEnd) 
{
    TraceEnd.Z += Recoil;
    Recoil += RecoilStep;
    float RecoilX = FMath::FRandRange(-XRecoil, XRecoil);
    TraceEnd.X += RecoilX;
}
