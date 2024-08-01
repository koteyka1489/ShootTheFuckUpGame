// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Weapon/STFUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);


ASTFUBaseWeapon::ASTFUBaseWeapon()
{
 
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    SetRootComponent(SkeletalMeshComponent);
}

void ASTFUBaseWeapon::Fire() 
{
    UE_LOG(LogBaseWeapon, Display, TEXT("TRA TA TA TA"));
}


void ASTFUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


