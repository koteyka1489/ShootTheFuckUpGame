// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Animations/STFUBaseAnimNotify.h"

void USTFUBaseAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotifide.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation);
}
