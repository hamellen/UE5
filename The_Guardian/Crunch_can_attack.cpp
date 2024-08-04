// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch_can_attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Crunch_ai_controller.h"
#include "TPS_Shooter.h"
UCrunch_can_attack::UCrunch_can_attack()
{
	NodeName = TEXT("CanAttack");
	attack_range = 1000.f;
}

bool UCrunch_can_attack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result=Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (pawn==nullptr) {
		return false;
	}

	auto target=Cast<ATPS_Shooter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Shooter_to_Attack"))));

	if (target == nullptr)
		return false;

	
	return result && target->GetDistanceTo(pawn)<= attack_range;
}
