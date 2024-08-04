// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Paladin_can_attakc.generated.h"

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UPaladin_can_attakc : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UPaladin_can_attakc();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
