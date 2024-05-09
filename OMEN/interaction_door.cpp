// Fill out your copyright notice in the Description page of Project Settings.


#include "interaction_door.h"

// Sets default values
Ainteraction_door::Ainteraction_door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>DOOR(TEXT("StaticMesh'/Game/LowPolySnowForest/Models/Cabin/SM_Cabin_Door_02.SM_Cabin_Door_02'"));
	sound_door = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/SFX/dorm-door-opening-6038.dorm-door-opening-6038'"));
	
	Tags.Add("door");

	if (DOOR.Succeeded()) {
		mesh->SetStaticMesh(DOOR.Object);
	}

	name = FName(TEXT("door"));
}

// Called when the game starts or when spawned
void Ainteraction_door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ainteraction_door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName Ainteraction_door::GetName()
{
	return name;
}

void Ainteraction_door::interaction()
{
	SetActorRelativeRotation(FRotator(0.f, -90.f, 0.f));

}

