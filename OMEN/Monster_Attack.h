// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Monster_Attack.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API UMonster_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:
	UMonster_Attack();

	UFUNCTION()
	void set_false();

	UPROPERTY()
	bool Is_attacking = false;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
