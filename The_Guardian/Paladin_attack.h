// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Paladin_attack.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UPaladin_attack : public UBTTaskNode
{
	GENERATED_BODY()
	

	bool bIsAttacking = false;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPaladin_attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
