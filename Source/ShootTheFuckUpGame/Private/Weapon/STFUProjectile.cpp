// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Weapon/STFUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet\GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LOG_PROJECTILE, All, All);

ASTFUProjectile::ASTFUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(CollisionComponent);

    MovementComponent               = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 3.0f;
}

void ASTFUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);

    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTFUProjectile::OnProjectileHit);

    SetLifeSpan(LifeSeconds);
}

void ASTFUProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(  //
        GetWorld(),                       //
        DamageAmount,                     //
        GetActorLocation(),               //
        DamageRadius,                     //
        UDamageType::StaticClass(),       //
        {GetOwner()},                     //
        this,                             //
        GetController(),                  //
        DoFullDamage                      //
    );

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 3.0f, false, 1.0f);

    Destroy();
}

AController* ASTFUProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());

    return Pawn ? Pawn->GetController() : nullptr;
}
