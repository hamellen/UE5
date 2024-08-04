// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Engine/DataTable.h"
#include "MyActor.h"
#include "Soldier_anim.generated.h"



UCLASS()
class THE_GUARDIAN_API USoldier_anim : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();


	UFUNCTION()
	void AnimNotify_reset_max_ammo();


public:

	UPROPERTY(EditAnywhere, Category = datatable)
	TObjectPtr<UDataTable> Soldier_Table;

	USoldier_anim();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = move)
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = pitch)
	float pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = direction)
	FVector direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = move)
	float direction_f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = move)
	float vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = run)
	bool Is_readytofire;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = run)
	bool Is_running;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = falling)
	bool Is_falling;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=weapon)
	EWeaponClass anim_current_weapon= EWeaponClass::E_AR_01;
	
	
	TObjectPtr<class ATPS_Shooter> player;

	FSoldierMontageRow* GetCharacterMontageRow(int number);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_AR01_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly )
	UAnimMontage* Montage_AR01_Empty_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_AR03_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage_AR03_Empty_Reload;


	void Reload_Empty_Montage();
	void Reload_Montage();
	void Fire();
};
