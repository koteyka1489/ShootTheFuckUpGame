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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USkeletalMeshComponent* SkeletalMeshComponent;

	virtual void Fire();

protected:
	virtual void BeginPlay() override;

};
