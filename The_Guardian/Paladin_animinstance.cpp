// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin_animinstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Paladin.h"
void UPaladin_animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (paladin) {
		player_targeted = paladin->is_targeted;
		fireto_rotate = UKismetMathLibrary::FindLookAtRotation(paladin->GetMesh()->GetSocketLocation(FName(TEXT("Bone_Turret_Head_LaserSocket"))), paladin->shooter_location);

	}
}

void UPaladin_animinstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	paladin = Cast<APaladin>(TryGetPawnOwner());

}

UPaladin_animinstance::UPaladin_animinstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>PALADIN_ATTACK(TEXT("/Script/Engine.AnimMontage'/Game/RoboDog/Robo_Dog/Animations/robodog_attack_montage.robodog_attack_montage'"));

	if (PALADIN_ATTACK.Succeeded()) {
		Paladin_attack = PALADIN_ATTACK.Object;
	}


	is_active = false;

	//paladin = Cast<APaladin>(TryGetPawnOwner());
}

void UPaladin_animinstance::Play_paladin_attack()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(Paladin_attack, 1.f);
	}
}

void UPaladin_animinstance::wakeup()
{
	is_active = true;

}
