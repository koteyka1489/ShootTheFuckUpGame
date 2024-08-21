// Shoot The Fuck Up Game. All Rights reserved!!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STFUBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEFUCKUPGAME_API ASTFUBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTFUBasePickUp();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
    USphereComponent* CollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	

	virtual void Tick(float DeltaTime) override;

};
