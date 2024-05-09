// Fill out your copyright notice in the Description page of Project Settings.


#include "first_dialogue_box.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Playerable_char.h"
// Sets default values
Afirst_dialogue_box::Afirst_dialogue_box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	overlap_com = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAP_VOLUME"));
	RootComponent = overlap_com;
	
}



void Afirst_dialogue_box::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("collision_detected"));

	auto detective = Cast<APlayerable_char>(Other);
	TArray<AActor*> Actors;
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "oldman", Actors);
	
	for (auto Actor : Actors) {
		
		FRotator normal = FRotator(detective->GetActorRotation().Pitch, UKismetMathLibrary::FindLookAtRotation(detective->GetActorLocation(),Actor->GetActorLocation()).Yaw, detective->GetActorRotation().Roll);
		detective->SetActorRelativeRotation(normal);
		auto controller = Cast<APlayerController>(detective->GetController());
		DisableInput(controller);
	}

	Destroy();

}



// Called when the game starts or when spawned
void Afirst_dialogue_box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Afirst_dialogue_box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

