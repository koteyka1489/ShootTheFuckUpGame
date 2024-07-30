// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Player/STFUCharacter.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Components\STFUCharacterMovementComponent.h"
#include "Components\STFUHealthComponent.h"
#include "Components\TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASTFUCharacter::ASTFUCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTFUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTFUHealthComponent>("HealthComponent");

    TextHealthComponent = CreateDefaultSubobject<UTextRenderComponent>("TextHealthComponent");
    TextHealthComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTFUCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(SpringArmComponent);
    check(CameraComponent);
    check(HealthComponent);
    check(TextHealthComponent);
    check(GetCharacterMovement());

    OnHealtChange(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTFUCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTFUCharacter::OnHealtChange);
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

float ASTFUCharacter::GetDotProductForwardVecAndVelocityVec() const
{
    const FVector ForwardVec  = GetActorForwardVector();
    const FVector VelocityVec = GetVelocity().GetSafeNormal();
    return FVector::DotProduct(ForwardVec, VelocityVec);
}

float ASTFUCharacter::GetDotProductRightVecAndVelocityVec() const
{
    const FVector RightVec    = GetActorRightVector();
    const FVector VelocityVec = GetVelocity().GetSafeNormal();
    return FVector::DotProduct(RightVec, VelocityVec);
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

void ASTFUCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Character is Death %s"), *GetName());

    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }

}

void ASTFUCharacter::OnHealtChange(float Health)
{
    TextHealthComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
