// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "My_Default_gun.h"
#include "AR_03.generated.h"

class USkeletalMeshComponent;

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API AAR_03 : public AMy_Default_gun
{
	GENERATED_BODY()
	

	AAR_03();

public:

	virtual void Reload() override;

	virtual void Fire(FVector endpoint) override;

	virtual void reset_gun_ammo();
};
