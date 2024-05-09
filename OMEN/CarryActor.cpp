// Fill out your copyright notice in the Description page of Project Settings.


#include "CarryActor.h"

// Sets default values
ACarryActor::ACarryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
}

// Called when the game starts or when spawned
void ACarryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACarryActor::SetMesh(int index)
{
	
}

