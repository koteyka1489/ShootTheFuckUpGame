// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Dev/STFUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTFUDevDamageActor::ASTFUDevDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ASTFUDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASTFUDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    int32 Segments = 24;
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, Segments, Color);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}
