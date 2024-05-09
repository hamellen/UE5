// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Homeless_Ai.generated.h"

/**
 * 
 */
UCLASS()
class OMEN_API AHomeless_Ai : public AAIController
{
	GENERATED_BODY()
	

public:

	AHomeless_Ai();


	virtual void OnPossess(APawn* InPawn) override;


	void homeless_move();
};
