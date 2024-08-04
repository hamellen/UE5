// Fill out your copyright notice in the Description page of Project Settings.


#include "footstep_notify.h"

Ufootstep_notify::Ufootstep_notify()
{


}

bool Ufootstep_notify::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const
{
	bool result=Super::Received_Notify(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("footstep channel activated"));

	FHitResult Hit;
	FVector start = MeshComp->GetOwner()->GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z - 500.f);


	bool isColl = GetWorld()->LineTraceSingleByChannel(Hit,start, end, ECC_GameTraceChannel8);

	if (isColl) {
		
		UE_LOG(LogTemp, Warning, TEXT("footstep channel hited"));

	}

	return result;
	
}
