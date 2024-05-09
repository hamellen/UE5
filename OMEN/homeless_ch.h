// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "homeless_ch.generated.h"

USTRUCT(BlueprintType)
struct FDialogue_list :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "dialogue")
	FString line_dialogue;

};




UCLASS()
class OMEN_API Ahomeless_ch : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Ahomeless_ch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	TArray<FString> first_dialogue_list;
	TArray<FString> second_dialogue_list;

	//class ATargetPoint* movepoint;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
