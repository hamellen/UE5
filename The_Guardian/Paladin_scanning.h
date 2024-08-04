// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Paladin_scanning.generated.h"

class APaladin;
class ATPS_Shooter;
/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API UPaladin_scanning : public UBTService
{
	GENERATED_BODY()
	

public:
	UPaladin_scanning();

	UPROPERTY()
	TObjectPtr<APaladin> paladin;

	UPROPERTY()
	TObjectPtr<ATPS_Shooter> player;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
