// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMelee.h"

// Sets default values
AMyMelee::AMyMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MELEE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MELEE(TEXT("StaticMesh'/Game/PROP/MELEE_WEAPON.MELEE_WEAPON'"));

	if (MELEE.Succeeded()) {
		mesh->SetStaticMesh(MELEE.Object);
	}
	mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AMyMelee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMelee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

