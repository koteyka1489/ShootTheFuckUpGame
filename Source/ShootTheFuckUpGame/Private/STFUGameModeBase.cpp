// Shoot The Fuck Up Game. All Rights reserved!!!

#include "STFUGameModeBase.h"
#include "Player\STFUCharacter.h"
#include "Player\STFUPlayerController.h"
#include "UI\STFUGameHUD.h"
#include "AIController.h"

ASTFUGameModeBase::ASTFUGameModeBase()
{
    DefaultPawnClass      = ASTFUCharacter::StaticClass();
    PlayerControllerClass = ASTFUPlayerController::StaticClass();
    HUDClass              = ASTFUGameHUD::StaticClass();
}

void ASTFUGameModeBase::StartPlay() 
{
    Super::StartPlay();

    SpawnBots();
}

UClass* ASTFUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawn;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTFUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayerNum -1; i++)
    {
        FActorSpawnParameters SpawnParam;
        SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto STFUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParam);
        RestartPlayer(STFUAIController);
    }

}
