// Shoot The Fuck Up Game. All Rights reserved!!!

#include "Player/STFUCharacter.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Components\STFUCharacterMovementComponent.h"
#include "Components\STFUHealthComponent.h"
#include "Components\TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Components/STFUWeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASTFUCharacter::ASTFUCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTFUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset            = FVector(0.f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTFUHealthComponent>("HealthComponent");

    TextHealthComponent = CreateDefaultSubobject<UTextRenderComponent>("TextHealthComponent");
    TextHealthComponent->SetupAttachment(GetRootComponent());
    TextHealthComponent->bOwnerNoSee = true;

    WeaponComponent = CreateDefaultSubobject<USTFUWeaponComponent>("WeaponComponent");

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
    check(WeaponComponent);

    OnHealtChange(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTFUCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTFUCharacter::OnHealtChange);
    LandedDelegate.AddDynamic(this, &ASTFUCharacter::OnGroundLanded);
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
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTFUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTFUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTFUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTFUWeaponComponent::Reload);
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
    WeaponComponent->StopFire();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ASTFUCharacter::OnHealtChange(float Health)
{
    TextHealthComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTFUCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const float LandingVelocity = -GetCharacterMovement()->Velocity.Z;
    UE_LOG(BaseCharacterLog, Display, TEXT("Landing %f"), LandingVelocity);

    if (LandingVelocity < FallDamageVelocityMinMax.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(FallDamageVelocityMinMax, FallDamageMinMax, LandingVelocity);
    UE_LOG(BaseCharacterLog, Display, TEXT("Damage %f"), FinalDamage);
    TakeDamage(FinalDamage, {}, nullptr, nullptr);
}
