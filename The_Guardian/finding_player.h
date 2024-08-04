// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "finding_player.generated.h"


class ACrunch;
/**
 * 
 */
UCLASS()
class THE_GUARDIAN_API Ufinding_player : public UBTService
{
	GENERATED_BODY()
	
public:

	Ufinding_player();

	UPROPERTY(EditAnywhere, Category = Crunch)
	TObjectPtr< ACrunch> crunch;
	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
