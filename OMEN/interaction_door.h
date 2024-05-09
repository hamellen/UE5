// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "displayname.h"
#include "interaction_door.generated.h"

UCLASS()
class OMEN_API Ainteraction_door : public AActor, public Idisplayname
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ainteraction_door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Can)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = name)
	FName name;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> sound_door;

	UPROPERTY(EditAnywhere)
	bool is_open;


	virtual FName GetName() override;

	void interaction();
};
