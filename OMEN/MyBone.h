// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "displayname.h"
#include "MyBone.generated.h"

UCLASS()
class OMEN_API AMyBone : public AActor, public Idisplayname
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBone();

	UPROPERTY(EditAnywhere, Category = Bone)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = name)
	FName name;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FName GetName() override;
};
