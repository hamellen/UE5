// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarryActor.generated.h"

UCLASS()
class OMEN_API ACarryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	void SetMesh(int index);
private:

	UPROPERTY(EditAnywhere, Category = Morphine, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* actor_mesh;

};
