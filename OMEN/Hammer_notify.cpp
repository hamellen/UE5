// Fill out your copyright notice in the Description page of Project Settings.


#include "Hammer_notify.h"
//#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

void UHammer_notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UE_LOG(LogTemp, Warning, TEXT("HAMMER BEGIN"));
}

void UHammer_notify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	UE_LOG(LogTemp, Warning, TEXT("HAMMER TICK"));
	FHitResult HitResult;
	//FCollisionQueryParams Params(NAME_Name,false,this);
	//Params.AddIgnoredActor(MeshComp->GetOwner());
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		MeshComp->GetSocketLocation("hammerattackhigh"),
		MeshComp->GetSocketLocation("hammerattackbottom"),
		FQuat::Identity,
		ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(20.0f));

	/*FVector Distance = MeshComp->GetSocketLocation("hammerattackhigh") - MeshComp->GetSocketLocation("hammerattackbottom");
	FVector Center = MeshComp->GetSocketLocation("hammerattackbottom") + Distance * 0.5;
	float HalfHeight = Distance.Size() / 2;
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;


	DrawDebugCapsule(GetWorld(), Center, HalfHeight, 10.f, FQuat::Identity, DrawColor, false, 1.f);*/

	
	if (bResult && HitResult.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR : %s"),*HitResult.GetActor()->GetName());
	}
}

void UHammer_notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("HAMMER END"));
}
