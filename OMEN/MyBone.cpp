// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBone.h"

// Sets default values
AMyBone::AMyBone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BONE"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BONE(TEXT("StaticMesh'/Game/bones/bone_fbx/bones_polySurface1.bones_polySurface1'"));

	Tags.Add(FName("bone"));

	if (BONE.Succeeded()) {
		mesh->SetStaticMesh(BONE.Object);
	}

	name = FName(TEXT("corpse bone"));
}

// Called when the game starts or when spawned
void AMyBone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AMyBone::GetName()
{



	return name;
}

