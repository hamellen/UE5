// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Monster_AIController.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Mon1(TEXT("AnimMontage'/Game/Monster/Animations/montage_monster_attack1.montage_monster_attack1'"));

	monster_dead = false;

	if (Mon1.Succeeded()) {
		monster_attack = Mon1.Object;
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto pawn = TryGetPawnOwner();
	
	if (IsValid(pawn)) {//속도 설정 
		speed = pawn->GetVelocity().Size();
	}
}

void UMonsterAnimInstance::PlayMonsterMontage()
{
	
	
	if (!Montage_IsPlaying(monster_attack)) {
		Montage_Play(monster_attack, 1.f);

		
	}

}

void UMonsterAnimInstance::AnimNotify_attack_end()//
{
	
	UE_LOG(LogTemp, Warning, TEXT("monster attack end"));


	AAIController* AI_C = UAIBlueprintHelperLibrary::GetAIController(GetOwningActor());

	auto monster_ai = Cast<AMonster_AIController>(AI_C);
	monster_ai->Reset_mode();
}

void UMonsterAnimInstance::AnimNotify_monster_dead()
{
	GetOwningActor()->Destroy();

}




