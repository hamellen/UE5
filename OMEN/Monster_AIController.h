// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Monster_AIController.generated.h"

DECLARE_MULTICAST_DELEGATE(FDele_end);

/**
 * 
 */
UCLASS()
class OMEN_API AMonster_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonster_AIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	

	UFUNCTION(BlueprintCallable)
	void activate_sound_trace();

	FDele_end dele_end;

	void Reset_mode();
	
	void activate_counter();
private:

	

	FTimerHandle TimerHandle;

	UPROPERTY()
	class UBehaviorTree* behaviortree;

	UPROPERTY()
	class UBlackboardData* blackboard_data;
};
