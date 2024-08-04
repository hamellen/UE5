// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/CharacterMovementComponent.h"
#include "Soldier_anim.h"
#include "TPS_Shooter.h"

void USoldier_anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (player) {
		direction = player->GetVelocity();
		speed = player->GetVelocity().Size();
		vertical = player->soldier_vertical;
		direction_f = CalculateDirection(direction, player->GetActorRotation());
		Is_falling = player->GetCharacterMovement()->IsFalling();
		anim_current_weapon = player->current_weapon;
		Is_running = player->soldier_run;
		Is_readytofire = player->soldier_readytofire;
		//pitch = player->soldier_pitch;



		if (player->GetBaseAimRotation().Pitch >= 180.0f) {
			pitch = player->GetBaseAimRotation().Pitch - 360.f;
		}
		else {
			pitch = player->GetBaseAimRotation().Pitch;
		}
	}

}

void USoldier_anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();



	player = Cast<ATPS_Shooter>(TryGetPawnOwner());
	
}

void USoldier_anim::AnimNotify_reset_max_ammo()
{

	player->reset_soldier_ammo();

}

USoldier_anim::USoldier_anim()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>MONTAGE_TABLE(TEXT("/Script/Engine.DataTable'/Game/DataTable/Soldier_montage.Soldier_montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_AR01_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/Player_soldier/Soldier_animation/AR/AR_01/Retargeted_AM_TP_CH_AR_01_Reload.Retargeted_AM_TP_CH_AR_01_Reload'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_AR01_EMPTY_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/Player_soldier/Soldier_animation/AR/AR_01/Retargeted_AM_TP_CH_AR_01_Reload_Empty.Retargeted_AM_TP_CH_AR_01_Reload_Empty'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_AR_FIRE(TEXT("/Script/Engine.AnimMontage'/Game/Player_soldier/Soldier_animation/AR/AR_Fire.AR_Fire'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_AR03_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/Player_soldier/Soldier_animation/AR/AR_03/Retargeted_AM_TP_CH_AR_03_Reload.Retargeted_AM_TP_CH_AR_03_Reload'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>MONTAGE_AR03_EMPTY_RELOAD(TEXT("/Script/Engine.AnimMontage'/Game/Player_soldier/Soldier_animation/AR/AR_03/Retargeted_AM_TP_CH_AR_03_Reload_Empty.Retargeted_AM_TP_CH_AR_03_Reload_Empty'"));
	



	if (MONTAGE_TABLE.Succeeded()) {
		Soldier_Table = MONTAGE_TABLE.Object;
		if (Soldier_Table != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("montage table is set"));
		}
		
	}
	if (MONTAGE_AR_FIRE.Succeeded()) {
		Montage_fire = MONTAGE_AR_FIRE.Object;
	}

	if (MONTAGE_AR01_RELOAD.Succeeded()) {
		Montage_AR01_Reload = MONTAGE_AR01_RELOAD.Object;
	}

	if (MONTAGE_AR01_EMPTY_RELOAD.Succeeded()) {
		Montage_AR01_Empty_Reload = MONTAGE_AR01_EMPTY_RELOAD.Object;
	}

	if (MONTAGE_AR03_RELOAD.Succeeded()) {
		Montage_AR03_Reload = MONTAGE_AR03_RELOAD.Object;
	}

	if (MONTAGE_AR03_EMPTY_RELOAD.Succeeded()) {
		Montage_AR03_Empty_Reload = MONTAGE_AR03_EMPTY_RELOAD.Object;
	}

	
}

FSoldierMontageRow* USoldier_anim::GetCharacterMontageRow(int number)
{
	return Soldier_Table->FindRow<FSoldierMontageRow>(*FString::FromInt(number),TEXT(""));
}

void USoldier_anim::Reload_Empty_Montage()
{
	EWeaponClass current = player->current_weapon;

	if (!IsAnyMontagePlaying()) {

		switch (current)
		{
		case EWeaponClass::E_AR_01:
			Montage_Play(Montage_AR01_Empty_Reload, 1.f);
			break;
		case EWeaponClass::E_AR_03:
			Montage_Play(Montage_AR03_Empty_Reload, 1.f);
			break;
		default:
			break;
		}


	}
}

void USoldier_anim::Reload_Montage()
{
	EWeaponClass current = player->current_weapon;

	//UE_LOG(LogTemp, Warning, TEXT("play reload in animinstance activate"));

	if (!IsAnyMontagePlaying()) {

		switch (current)
		{
		case EWeaponClass::E_AR_01:
			//Montage_Play(GetCharacterMontageRow(1)->reload, 1.f);
			Montage_Play(Montage_AR01_Reload, 1.f);
			//UE_LOG(LogTemp, Warning, TEXT("ar_01 reload animation play"));
			break;
		case EWeaponClass::E_AR_03:
			Montage_Play(Montage_AR03_Reload, 1.f);
			break;
		default:
			break;
		}

	}

}

void USoldier_anim::Fire()
{
	//EShootType current = player->current_shoot_type;
	if (!Montage_IsPlaying(Montage_AR01_Reload) && !Montage_IsPlaying(Montage_AR01_Empty_Reload) && Is_readytofire) {

		Montage_Play(Montage_fire, 1.f);
	}
	
}


