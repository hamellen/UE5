// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBandage.h"

// Sets default values
AMyBandage::AMyBandage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MYBANDAGE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>BANDAGE(TEXT("StaticMesh'/Game/PROP/bandage-roll/source/bandageroll_bandageroll.bandageroll_bandageroll'"));

	Tags.Add(FName("bandage"));
	if (BANDAGE.Succeeded()) {
		mesh->SetStaticMesh(BANDAGE.Object);
	}
	//mesh->SetCollisionProfileName(TEXT("NoCollision"));
	name = FName(TEXT("bandage"));
}


// Called when the game starts or when spawned
void AMyBandage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBandage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AMyBandage::GetName()
{
	return name;
}

