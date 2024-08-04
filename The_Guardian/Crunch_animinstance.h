// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Crunch_animinstance.generated.h"




/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UCrunch_animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();
public:

	
	

	UCrunch_animinstance();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=move)
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool activate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool is_burst_mode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=crunch_attack)
	UAnimMontage* Crunch_jumpattack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = crunch_attack)
	UAnimMontage* Crunch_meleeattack_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = crunch_attack)
	UAnimMontage* Crunch_meleeattack_2;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = crunch_attack)
	UAnimMontage* Crunch_meleeattack_3;


	UPROPERTY(EditAnywhere)
	TObjectPtr<class ACrunch> crunch;

	UFUNCTION()
	void AnimNotify_crunch_montage_ended();

	void Play_crunch_melee_attack();
	void Play_crunch_jump_attack();
};
