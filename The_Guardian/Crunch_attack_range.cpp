// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch_attack_range.h"
#include "Crunch.h"
#include "DrawDebugHelpers.h"
void UCrunch_attack_range::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, TotalDuration, EventReference);
	crunch = Cast<ACrunch>(MeshComp->GetOwner());
}

void UCrunch_attack_range::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false,crunch );


	bool bResult=GetWorld()->SweepSingleByChannel(HitResult,
		MeshComp->GetSocketLocation(FName(TEXT("Crunch_attack_high"))),
		MeshComp->GetSocketLocation(FName(TEXT("Crunch_attack_bottom"))),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(30.f),
		Params);

	FVector Distance = MeshComp->GetSocketLocation("Crunch_attack_high") - MeshComp->GetSocketLocation("Crunch_attack_bottom");
	FVector Center = MeshComp->GetSocketLocation("Crunch_attack_bottom") + Distance * 0.5;
	float HalfHeight = Distance.Size() / 2;
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;


	DrawDebugCapsule(GetWorld(), Center, HalfHeight, 30.f, FQuat::Identity, DrawColor, false, 1.f);
}
