// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch_animinstance.h"
#include "Crunch.h"
void UCrunch_animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (crunch) {
		speed = crunch->GetVelocity().Size();
	}

}

void UCrunch_animinstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	is_burst_mode = false;
	activate = false;
	crunch = Cast<ACrunch>(TryGetPawnOwner());

}

UCrunch_animinstance::UCrunch_animinstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>CRUNCH_JUMP_ATTACK(TEXT("/Script/Engine.AnimMontage'/Game/Monster/Crunch/Crunch_animation/Retargeted_Animatronic_Attack_JumpForward_Montage.Retargeted_Animatronic_Attack_JumpForward_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>CRUNCH_MELEE_1(TEXT("/Script/Engine.AnimMontage'/Game/Monster/Crunch/Crunch_animation/Retargeted_Animatronic_Attack_PowerSwing02_Forward_Montage.Retargeted_Animatronic_Attack_PowerSwing02_Forward_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>CRUNCH_MELEE_2(TEXT("/Script/Engine.AnimMontage'/Game/Monster/Crunch/Crunch_animation/Retargeted_Animatronic_Attack_Swing01_Forward_Montage.Retargeted_Animatronic_Attack_Swing01_Forward_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>CRUNCH_MELEE_3(TEXT("/Script/Engine.AnimMontage'/Game/Monster/Crunch/Crunch_animation/Retargeted_Animatronic_Attack_Swing02_Forward_Montage.Retargeted_Animatronic_Attack_Swing02_Forward_Montage'"));

	if (CRUNCH_JUMP_ATTACK.Succeeded()) {
		Crunch_jumpattack = CRUNCH_JUMP_ATTACK.Object;
	}
	if (CRUNCH_MELEE_1.Succeeded()) {
		Crunch_meleeattack_1 = CRUNCH_MELEE_1.Object;
	}
	if (CRUNCH_MELEE_2.Succeeded()) {
		Crunch_meleeattack_2 = CRUNCH_MELEE_2.Object;
	}
	if (CRUNCH_MELEE_3.Succeeded()) {
		Crunch_meleeattack_3 = CRUNCH_MELEE_3.Object;
	}

}

void UCrunch_animinstance::AnimNotify_crunch_montage_ended()
{
	
}

void UCrunch_animinstance::Play_crunch_melee_attack()
{
	if (!IsAnyMontagePlaying()) {
		
		int random = FMath::RandRange(1, 3);

		switch (random)
		{
		case 1:
			Montage_Play(Crunch_meleeattack_1, 1.f);
			break;

		case 2:
			Montage_Play(Crunch_meleeattack_2, 1.f);
			break;

		case 3:
			Montage_Play(Crunch_meleeattack_3, 1.f);
			break;
		}
		


	}


}

void UCrunch_animinstance::Play_crunch_jump_attack()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Crunch_jumpattack, 1.f);
	}

}
