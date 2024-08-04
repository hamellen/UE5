// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AR_03_animinstance.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UAR_03_animinstance : public UAnimInstance
{
	GENERATED_BODY()
	

	
	virtual void NativeInitializeAnimation();

public:

	UAR_03_animinstance();

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_reload_empty;

	void Play_gun_fire();
	void Play_reload_empty();
	void Play_reload();

};
