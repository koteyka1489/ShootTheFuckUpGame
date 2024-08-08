// Shoot The Fuck Up Game. All Rights reserved!!!


#include "Animations/STFUEquipFinishedAnimNotify.h"

void USTFUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{

    OnNotifide.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);

}
