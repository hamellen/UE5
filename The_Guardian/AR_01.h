// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "My_Default_gun.h"
#include "AR_01.generated.h"




/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API AAR_01 : public AMy_Default_gun
{
	GENERATED_BODY()
	
	AAR_01();

public:


	virtual void Reload() override;


	virtual void Fire(FVector endpoint) override;

	virtual void reset_gun_ammo();

	void play_reload_sound(int index);
};
