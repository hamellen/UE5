// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMorphine.h"

// Sets default values
AMyMorphine::AMyMorphine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MORPHINE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MORPHINE(TEXT("StaticMesh'/Game/PROP/morphine-auto-injector/source/Morhpine_Auto_Injector.Morhpine_Auto_Injector'"));

	Tags.Add(FName("morphine"));
	if (MORPHINE.Succeeded()) {
		mesh->SetStaticMesh(MORPHINE.Object);
	}
	//mesh->SetCollisionProfileName(TEXT("NoCollision"));
	name = FName(TEXT("syringe"));
}


// Called when the game starts or when spawned
void AMyMorphine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMorphine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AMyMorphine::GetName()
{

	return name;
}

