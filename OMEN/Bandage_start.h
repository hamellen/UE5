// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Bandage_start.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API UBandage_start : public UAnimNotify
{
	GENERATED_BODY()



	UPROPERTY(VisibleAnywhere,Category=Bandage, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* bandage;
	
public:
	virtual bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	
};
