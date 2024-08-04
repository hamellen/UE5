// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AR_01_animinstance.generated.h"

class AAR_01;
/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UAR_01_animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
	virtual void NativeInitializeAnimation();

public:

	UAR_01_animinstance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_reload_empty;

	UFUNCTION()
	void AnimNotify_gun_magazine_out();

	UFUNCTION()
	void AnimNotify_gun_magazine_in();

	UFUNCTION()
	void AnimNotify_gun_stick();

	TObjectPtr<AAR_01> gun;


	void Play_gun_fire();
	void Play_reload_empty();
	void Play_reload();
};
