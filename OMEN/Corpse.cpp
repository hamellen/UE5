// Fill out your copyright notice in the Description page of Project Settings.


#include "Corpse.h"

// Sets default values
ACorpse::ACorpse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CORPSE"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CORPSE(TEXT("StaticMesh'/Game/BodyBag_Corpses/corpse_static.corpse_static'"));


	Tags.Add(FName("corpse"));

	if (CORPSE.Succeeded()) {
		mesh->SetStaticMesh(CORPSE.Object);
	}

	name = FName(TEXT("corpse"));
}

// Called when the game starts or when spawned
void ACorpse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorpse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName ACorpse::GetName()
{
	return name;
}

