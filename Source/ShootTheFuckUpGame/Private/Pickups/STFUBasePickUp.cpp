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
	
}


void ASTFUBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(PickUpLog, Display, TEXT("Pick Up Overlap"));

    Destroy();
}

void ASTFUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

