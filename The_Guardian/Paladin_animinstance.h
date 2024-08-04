// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Paladin_animinstance.generated.h"

class APaladin;
/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UPaladin_animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();


public:

	UPaladin_animinstance();

	UPROPERTY(EditAnywhere,Category=paladin)
	TObjectPtr<APaladin> paladin;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool is_active;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator fireto_rotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool player_targeted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = crunch_attack)
	UAnimMontage* Paladin_attack;

	void Play_paladin_attack();

	void wakeup();
};
