// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "player_animinstance.generated.h"

DECLARE_DELEGATE(FDelesecure);

/**
 * 
 */
UCLASS()
class OMEN_API Uplayer_animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
	

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_can_create();

	UFUNCTION()
	void AnimNotify_recovery_hp();

	UFUNCTION()
	void AnimNotify_speedup();
	

	UFUNCTION()
	void AnimNotify_syringe_create();

	

	UFUNCTION()
	void AnimNotify_bandage_create();


	UFUNCTION()
	void AnimNotify_prop_delete();

	UFUNCTION()
	void AnimNotify_re_weapon();

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Run, meta = (AllowPrivateAccess = "true"))
	bool IsRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Hammer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Bandage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Drink;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage_Syringe;

	FName drinksocket, morphinesocket, bandagesocket, meleesocket;
	


public:
	Uplayer_animinstance();

	void PlayHammerAttack();
	void PlayBandageMotion();
	void PlayDrinkMotion();
	void PlaySyringeMotion();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vertical)
	float vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Horizon)
	float horizon;


	FDelesecure Fuc_secure_end;
};
