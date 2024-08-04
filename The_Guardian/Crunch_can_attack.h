// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Crunch_can_attack.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UCrunch_can_attack : public UBTDecorator
{
	GENERATED_BODY()
public:

	UCrunch_can_attack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
	UPROPERTY(EditAnywhere,Category=Attack_range)
	float  attack_range;
	
};
