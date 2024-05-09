// Fill out your copyright notice in the Description page of Project Settings.


#include "player_animinstance.h"
#include "Playerable_char.h"
#include "MyCan.h"
#include "MyBandage.h"
#include "MyMorphine.h"
#include "MyMelee.h"
void Uplayer_animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	
	if (IsValid(pawn)) {
		auto detective = Cast<APlayerable_char>(pawn);
		
		vertical = detective->input_vertical;
		horizon = detective->input_horizon;
		IsRun = detective->IS_RUN;
	}
}

void Uplayer_animinstance::AnimNotify_can_create()
{
	UE_LOG(LogTemp, Warning, TEXT("Drink Create"));

	auto currentmesh = GetWorld()->SpawnActor<AMyCan>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (currentmesh) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		currentmesh->AttachToComponent(detective->GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			drinksocket);
	}
}

void Uplayer_animinstance::AnimNotify_recovery_hp()
{
	auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
	detective->player_recovery();
}

void Uplayer_animinstance::AnimNotify_speedup()
{
	auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
	detective->speedup();
}

//void Uplayer_animinstance::equip_melee()
//{
//	auto currentmesh = GetWorld()->SpawnActor<AMyMelee>(FVector::ZeroVector, FRotator::ZeroRotator);
//	if (currentmesh) {
//		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
//		currentmesh->AttachToComponent(detective->GetMesh(),
//			FAttachmentTransformRules::SnapToTargetIncludingScale,
//			meleesocket);
//	}
//}



void Uplayer_animinstance::AnimNotify_syringe_create()
{
	auto currentmesh = GetWorld()->SpawnActor<AMyMorphine>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (currentmesh) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		currentmesh->AttachToComponent(detective->GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			morphinesocket);
	}
}



void Uplayer_animinstance::AnimNotify_bandage_create()
{
	auto currentmesh = GetWorld()->SpawnActor<AMyBandage>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (currentmesh) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		currentmesh->AttachToComponent(detective->GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			bandagesocket);
	}
}



void Uplayer_animinstance::AnimNotify_prop_delete()
{
	auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
	TArray<AActor*> AttachedActors;
	detective->GetAttachedActors(AttachedActors);
	for (auto* Attached : AttachedActors)
	{
		Attached->Destroy();
	}
}

void Uplayer_animinstance::AnimNotify_re_weapon()
{
	auto currentmesh = GetWorld()->SpawnActor<AMyMelee>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (currentmesh) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		currentmesh->AttachToComponent(detective->GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			meleesocket);
	}

}



void Uplayer_animinstance::PlayHammerAttack()
{
	if (!IsAnyMontagePlaying()) {
		
		Montage_Play(Montage_Hammer, 1.f);
		
	}
	
}

void Uplayer_animinstance::PlayBandageMotion()
{
	UE_LOG(LogTemp, Warning, TEXT("Bandage START"));
	
	if (!IsAnyMontagePlaying()) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		detective->num_bandage--;
		detective->decrease_prop(2);
		Montage_Play(Montage_Bandage, 1.f);
	}
}

void Uplayer_animinstance::PlayDrinkMotion()
{
	UE_LOG(LogTemp, Warning, TEXT("Drink START"));
	if (!IsAnyMontagePlaying()) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		detective->num_drink--;
		detective->decrease_prop(1);
		Montage_Play(Montage_Drink, 1.f);
	}
}

void Uplayer_animinstance::PlaySyringeMotion()
{
	UE_LOG(LogTemp, Warning, TEXT("Syringe START"));
	if (!IsAnyMontagePlaying()) {
		auto detective = Cast<APlayerable_char>(TryGetPawnOwner());
		detective->num_morphine--;
		detective->decrease_prop(3);
		Montage_Play(Montage_Syringe, 1.f);
	}
}

Uplayer_animinstance::Uplayer_animinstance()
{
	
	drinksocket = FName(TEXT("drinksocket"));
	morphinesocket = FName(TEXT("syringesocket"));
	bandagesocket = FName(TEXT("bandagesocket"));
	meleesocket = FName(TEXT("socket_hammer"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>HAMMER(TEXT("AnimMontage'/Game/DetectiveCharacter/detective_animation/melee/Montage_hammer_attack.Montage_hammer_attack'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>BANDAGE(TEXT("AnimMontage'/Game/DetectiveCharacter/detective_animation/Bandage_04_Retargeted_Montage.Bandage_04_Retargeted_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>DRINK(TEXT("AnimMontage'/Game/DetectiveCharacter/detective_animation/Drink_06_Retargeted_Montage.Drink_06_Retargeted_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SYRINGE(TEXT("AnimMontage'/Game/DetectiveCharacter/detective_animation/Syringe_01_Retargeted_Montage.Syringe_01_Retargeted_Montage'"));



	if (HAMMER.Succeeded()) {
		Montage_Hammer = HAMMER.Object;
	}
	
	if (BANDAGE.Succeeded()) {
		Montage_Bandage = BANDAGE.Object;
	}
	if (DRINK.Succeeded()) {
		Montage_Drink = DRINK.Object;
	}
	if (SYRINGE.Succeeded()) {
		Montage_Syringe = SYRINGE.Object;
	}

	//equip_melee();
}
