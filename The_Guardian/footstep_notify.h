// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "footstep_notify.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API Ufootstep_notify : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	Ufootstep_notify();

	virtual bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const;

};
