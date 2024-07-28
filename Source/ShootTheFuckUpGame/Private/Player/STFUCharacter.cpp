// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Player/STFUCharacter.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Components\STFUCharacterMovementComponent.h"

// Sets default values
ASTFUCharacter::ASTFUCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTFUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
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
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTFUCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTFUCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTFUCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookRight", this, &ASTFUCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTFUCharacter::Jump);
    PlayerInputComponent->BindAction("Runing", IE_Pressed, this, &ASTFUCharacter::RuningOn);
    PlayerInputComponent->BindAction("Runing", IE_Released, this, &ASTFUCharacter::RuningOff);
}

void ASTFUCharacter::MoveForward(float Amount)
{
    IsMoveForward = Amount > 0.f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTFUCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTFUCharacter::RuningOn()
{
    IsRuning = true;
}

void ASTFUCharacter::RuningOff()
{
    IsRuning = false;
}
