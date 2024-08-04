// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Crunch_Attack_Task.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UCrunch_Attack_Task : public UBTTaskNode
{
	GENERATED_BODY()
	
	bool bIsAttacking = false;

public:

	UCrunch_Attack_Task();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	void Set_attaking_false();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
