// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTFUBaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    FColor LineColor = FColor::Red;

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

	void MakeShot();
};
