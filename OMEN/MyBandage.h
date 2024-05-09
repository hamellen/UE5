// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "displayname.h"
#include "MyBandage.generated.h"

UCLASS()
class OMEN_API AMyBandage : public AActor, public Idisplayname
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBandage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = name)
	FName name;

	virtual FName GetName() override;

private:
	UPROPERTY(EditAnywhere,Category=Bandage, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;
};
