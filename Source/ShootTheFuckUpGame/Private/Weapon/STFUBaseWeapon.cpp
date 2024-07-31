// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Weapon/STFUBaseWeapon.h"

// Sets default values
ASTFUBaseWeapon::ASTFUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    SetRootComponent(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void ASTFUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


