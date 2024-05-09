// Fill out your copyright notice in the Description page of Project Settings.


#include "footsound_notify.h"
//#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
bool Ufootsound_notify::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Received_Notify(MeshComp, Animation, EventReference);

	FHitResult HitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(MeshComp->GetOwner());
	FVector initial_vector = MeshComp->GetOwner()->GetActorLocation();

	FVector floor_vector(initial_vector.X, initial_vector.Y, initial_vector.Z - 500);

	bool bResult=GetWorld()->LineTraceSingleByChannel(
		HitResult,
		initial_vector,
		floor_vector,
		ECollisionChannel::ECC_Visibility,
		params,
		FCollisionResponseParams());

	

	return false;
}
