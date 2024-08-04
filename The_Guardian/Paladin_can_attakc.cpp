// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin_can_attakc.h"
#include "Paladin.h"
#include "Paladin_ai_controller.h"
UPaladin_can_attakc::UPaladin_can_attakc()
{
	NodeName = TEXT("Is_Paladin_Active?");
}

bool UPaladin_can_attakc::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto paladin = Cast<APaladin>(OwnerComp.GetAIOwner()->GetPawn());

	if (paladin == nullptr) {
		return false;
	}

	return  paladin->is_active;
}
