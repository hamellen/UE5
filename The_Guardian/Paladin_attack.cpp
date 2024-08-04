// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin_attack.h"
#include "Paladin.h"
#include "Paladin_ai_controller.h"

void UPaladin_attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsAttacking == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}


}

UPaladin_attack::UPaladin_attack()
{
	NodeName = TEXT("PALADIN_ATTACK");
}

EBTNodeResult::Type UPaladin_attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto paladin = Cast<APaladin>(OwnerComp.GetAIOwner()->GetPawn());
	if (paladin == nullptr) {
		return EBTNodeResult::Failed;
	}

	paladin->play_attack();
	bIsAttacking = true;

	paladin->dele_paladin_montage_ended.AddLambda([this]() {
		bIsAttacking = false;
		});





	return result;
}
