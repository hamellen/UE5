// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UMonsterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster_speed, meta = (AllowPrivateAccess = "true"))
	float speed;

	


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MONSTER_ATTACK, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* monster_attack;
public:
	void PlayMonsterMontage();


	UFUNCTION()
	void AnimNotify_attack_end();

	UFUNCTION()
	void AnimNotify_monster_dead();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Is_dead)
	bool monster_dead;

private:

		

};
