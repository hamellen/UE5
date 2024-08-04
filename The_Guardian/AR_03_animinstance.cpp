// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_03_animinstance.h"



void UAR_03_animinstance::NativeInitializeAnimation()
{
	
}

UAR_03_animinstance::UAR_03_animinstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_FIRE(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_WEP_AR_03_Fire.AM_WEP_AR_03_Fire'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_TP_WEP_AR_03_Reload.AM_TP_WEP_AR_03_Reload'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_RELOAD_EMPTY(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_TP_WEP_AR_03_Reload_Empty.AM_TP_WEP_AR_03_Reload_Empty'"));

	if (MONTAGE_GUN_FIRE.Succeeded()) {
		Montage_fire = MONTAGE_GUN_FIRE.Object;
	}
	if (MONTAGE_GUN_RELOAD .Succeeded()) {
		Montage_reload = MONTAGE_GUN_RELOAD .Object;
	}
	if (MONTAGE_GUN_RELOAD_EMPTY.Succeeded()) {
		Montage_reload_empty = MONTAGE_GUN_RELOAD_EMPTY.Object;
	}
}

void UAR_03_animinstance::Play_gun_fire()
{

	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage_fire, 1.f);
	}
}

void UAR_03_animinstance::Play_reload_empty()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage_reload_empty, 1.f);
	}
}

void UAR_03_animinstance::Play_reload()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage_reload, 1.f);
	}
}
