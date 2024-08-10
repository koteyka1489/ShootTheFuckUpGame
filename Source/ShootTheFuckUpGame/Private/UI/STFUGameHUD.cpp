// Shoot The Fuck Up Game. All Rights reserved!!!

#include "UI/STFUGameHUD.h"
#include "Engine\Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTFUGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTFUGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerWidget)
    {
        PlayerWidget->AddToViewport();
    }
}

void ASTFUGameHUD::DrawCrossHair()
{

    const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

    const float HalfLine         = 10.0f;
    const float LineThickness    = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLine, Center.Max, Center.Min + HalfLine, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLine, Center.Min, Center.Max + HalfLine, LineColor, LineThickness);
}
