// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Attack.h"
#include "Monster.h"
#include "Monster_AIController.h"
UMonster_Attack::UMonster_Attack()
{
	bNotifyTick = true;



}

void UMonster_Attack::set_false()
{
	Is_attacking = false;
}



EBTNodeResult::Type UMonster_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto monster=Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (monster == nullptr) {
		return EBTNodeResult::Failed;
	}
	monster->MonsterAttack();
	Is_attacking = true;

	auto ai_c=Cast<AMonster_AIController>(OwnerComp.GetAIOwner());
	if (ai_c) {
		ai_c->dele_end.AddUFunction(this, FName("set_false"));
	}
	return Result;
}

void UMonster_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (Is_attacking == false) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
