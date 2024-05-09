// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCan.h"

// Sets default values
AMyCan::AMyCan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CAN"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CAN(TEXT("StaticMesh'/Game/BottlePack/Models/A/SM_BeerCanA_A.SM_BeerCanA_A'"));

	Tags.Add(FName("can"));

	if (CAN.Succeeded()) {
		mesh->SetStaticMesh(CAN.Object);
	}
	//mesh->SetCollisionProfileName(TEXT("NoCollision"));
	name = FName(TEXT("boostup beverage"));
}

// Called when the game starts or when spawned
void AMyCan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AMyCan::GetName()
{


	return name;
}



