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

void ASTFUBaseWeapon::StartFire() {}

void ASTFUBaseWeapon::StopFire() {}

void ASTFUBaseWeapon::MakeShot() {}

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

void ASTFUBaseWeapon::GetTraceStartAndEnd(FVector& TraceStart, FVector& TraceEnd) {}

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

FVector ASTFUBaseWeapon::GetSocketWorldLocation()
{
    return GetSocketTranform().GetLocation();
}
