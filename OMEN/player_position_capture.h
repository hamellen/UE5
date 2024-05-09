// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "player_position_capture.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API Uplayer_position_capture : public UBTService
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = capture)
	float capture_range;

	Uplayer_position_capture();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
};
