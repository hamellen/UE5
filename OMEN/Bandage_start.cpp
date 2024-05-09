// Fill out your copyright notice in the Description page of Project Settings.


#include "Bandage_start.h"



bool UBandage_start::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	bandage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BANDAGE"));

	



	return false;
}
