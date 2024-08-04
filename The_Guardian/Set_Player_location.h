// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Set_Player_location.generated.h"


class ATPS_Shooter;
/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API USet_Player_location : public UBTService
{
	GENERATED_BODY()
	
public:

	USet_Player_location();


	UPROPERTY()
	TObjectPtr<ATPS_Shooter> player;
	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
