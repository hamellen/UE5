// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_01_animinstance.h"
#include "AR_01.h"


void UAR_01_animinstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	gun = Cast<AAR_01>(TryGetPawnOwner());
}

UAR_01_animinstance::UAR_01_animinstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_FIRE(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_WEP_AR_01_Fire.AM_WEP_AR_01_Fire'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_TP_WEP_AR_01_Reload.AM_TP_WEP_AR_01_Reload'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_GUN_RELOAD_EMPTY(TEXT("/Script/Engine.AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/Animations/AM_TP_WEP_AR_01_Reload_Empty.AM_TP_WEP_AR_01_Reload_Empty'"));

	if (MONTAGE_GUN_FIRE.Succeeded()) {
		Montage_fire = MONTAGE_GUN_FIRE.Object;
	}
	if (MONTAGE_GUN_RELOAD.Succeeded()) {
		Montage_reload = MONTAGE_GUN_RELOAD.Object;
	}
	if (MONTAGE_GUN_RELOAD_EMPTY.Succeeded()) {
		Montage_reload_empty = MONTAGE_GUN_RELOAD_EMPTY.Object;
	}

	//gun = Cast<AAR_01>(TryGetPawnOwner());
}

void UAR_01_animinstance::AnimNotify_gun_magazine_out()
{
	gun->play_reload_sound(1);
	//UE_LOG(LogTemp, Warning, TEXT("ar _01 magazine out"));
}

void UAR_01_animinstance::AnimNotify_gun_magazine_in()
{
	gun->play_reload_sound(2);
	//UE_LOG(LogTemp, Warning, TEXT("ar _01 magazine in"));
}

void UAR_01_animinstance::AnimNotify_gun_stick()
{
	gun->play_reload_sound(3);
	//UE_LOG(LogTemp, Warning, TEXT("ar _01 stick"));

}

void UAR_01_animinstance::Play_gun_fire()
{
	Montage_Play(Montage_fire, 1.f);
}

void UAR_01_animinstance::Play_reload_empty()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage_reload_empty, 1.f);
	}
}

void UAR_01_animinstance::Play_reload()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Montage_reload, 1.f);
		UE_LOG(LogTemp, Warning, TEXT("ar _01_reload_animation_anim   playing"));
	}
}
