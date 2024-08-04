// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Paladin_ai_controller.generated.h"

class UBlackboardData;
class UBehaviorTree;
class APaladin;

/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API APaladin_ai_controller : public AAIController
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, Category = Crunch)
	TObjectPtr<UBlackboardData> blackboard_data;

	UPROPERTY(EditAnywhere, Category = Crunch)
	TObjectPtr< UBehaviorTree> behaviortree;


	FTimerHandle TimerHandle;
public:

	UPROPERTY(EditAnywhere, Category = Crunch)
	TObjectPtr< APaladin> paladin;


	APaladin_ai_controller();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void Player_check();
};
