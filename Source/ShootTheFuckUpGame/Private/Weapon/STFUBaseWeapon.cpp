// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUBaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework\Character.h"
#include "GameFramework\Controller.h"

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

void ASTFUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("TRA TA TA TA"));
    MakeShot();
}

void ASTFUBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;

    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller) return;

    FVector ViewLocation;
    FRotator ViewRotation;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    const FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);

    const FVector TraceStart = ViewLocation; //    SocketTransform.GetLocation();
    const FVector ShootDirection = ViewRotation.Vector();  // SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd       = TraceStart + ShootDirection * TraceMaxDistance;

    

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, LineColor, false, 3.0f, 0u, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Cyan, false, 1.0f, 0u, 1.0f);
        UE_LOG(LogBaseWeapon, Display, TEXT("Bone - %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, LineColor, false, 3.0f, 0u, 3.0f);
    }
}
