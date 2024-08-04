// Fill out your copyright notice in the Description page of Project Settings.


#include "UObject/ConstructorHelpers.h"

#include "Soldier_SK_Container.h"

// Sets default values for this component's properties
USoldier_SK_Container::USoldier_SK_Container()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>SK_TABLE(TEXT("/Script/Engine.DataTable'/Game/DataTable/Sodier_Mesh.Sodier_Mesh'"));

	if (SK_TABLE.Object) {
		Soldier_Table = SK_TABLE.Object;
	}

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USoldier_SK_Container::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USoldier_SK_Container::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

