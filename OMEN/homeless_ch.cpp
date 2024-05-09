// Fill out your copyright notice in the Description page of Project Settings.


#include "homeless_ch.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
Ahomeless_ch::Ahomeless_ch()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK(TEXT("SkeletalMesh'/Game/NPC_Homeless_Man/Mesh/Sk_NPC_Homeless_Man.Sk_NPC_Homeless_Man'"));

	if (SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK.Object);
	}

	//TArray<AActor*> Actors;
	//Tags.Add(FName("oldman"));

	//UGameplayStatics::GetAllActorsWithTag(GetWorld(), "homeless_target", Actors);

	//for (auto Actor : Actors) {
	//	movepoint = Cast<ATargetPoint>(Actor);
	//}

}

// Called when the game starts or when spawned
void Ahomeless_ch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ahomeless_ch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Ahomeless_ch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

