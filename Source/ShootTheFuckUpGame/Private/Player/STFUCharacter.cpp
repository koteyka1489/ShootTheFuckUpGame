// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Player/STFUCharacter.h"
#include "Camera\CameraComponent.h"

// Sets default values
ASTFUCharacter::ASTFUCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTFUCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASTFUCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTFUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
