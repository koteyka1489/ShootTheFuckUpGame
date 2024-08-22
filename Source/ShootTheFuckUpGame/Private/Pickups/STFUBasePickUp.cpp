// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Pickups/STFUBasePickUp.h"
#include "Components\SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PickUpLog, All, All)

ASTFUBasePickUp::ASTFUBasePickUp()
{

    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTFUBasePickUp::BeginPlay()
{
    Super::BeginPlay();
    check(CollisionComponent);
}

void ASTFUBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (GivePickUpTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool ASTFUBasePickUp::GivePickUpTo(APawn* Pawn)
{
    return false;
}

void ASTFUBasePickUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTFUBasePickUp::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle TimerManager;
    GetWorldTimerManager().SetTimer(TimerManager, this, &ASTFUBasePickUp::Respawn, RespawnTime);
}

void ASTFUBasePickUp::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}
