// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomMoveFinding.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API UBTTask_RandomMoveFinding : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_RandomMoveFinding();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float random_range;
};
