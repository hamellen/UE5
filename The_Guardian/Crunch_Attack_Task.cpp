// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch_Attack_Task.h"
#include "Crunch.h"
#include "Crunch_ai_controller.h"
#include "BehaviorTree/BlackboardComponent.h"
UCrunch_Attack_Task::UCrunch_Attack_Task()
{
	NodeName = TEXT("CRUNCH_ATTACK");
}

void UCrunch_Attack_Task::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (bIsAttacking == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}


}

void UCrunch_Attack_Task::Set_attaking_false()
{
	bIsAttacking = false;
}

EBTNodeResult::Type UCrunch_Attack_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result=Super::ExecuteTask(OwnerComp, NodeMemory);

	auto crunch = Cast<ACrunch>(OwnerComp.GetAIOwner()->GetPawn());
	if (crunch == nullptr) {
		return EBTNodeResult::Failed;
	}
	
	crunch->Play_meleeattack();
	bIsAttacking = true;

	crunch->dele_crunch_montage_ended.AddLambda([this]() {
		bIsAttacking = false;
		});


	return result;
}
