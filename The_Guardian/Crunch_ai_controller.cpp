// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch_ai_controller.h"
#include "Engine/TargetPoint.h"
#include "Crunch.h"
#include "TPS_Shooter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
ACrunch_ai_controller::ACrunch_ai_controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("/Script/AIModule.BlackboardData'/Game/Monster/Crunch/Crunch_BB.Crunch_BB'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/Crunch/Crunch_BT.Crunch_BT'"));

	if (BD.Succeeded()) {
		blackboard_data = BD.Object;
	}

	if (BT.Succeeded()) {
		behaviortree = BT.Object;
	}
}

void ACrunch_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;

	crunch = Cast<ACrunch>(GetPawn());

	/*if (crunch == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("crunch is not exist"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("crunch is exist"));
	}*/

	First_initialize_position();


	/*TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SEARCHING_POINT"), Actors);
	central_point_location = Cast<ATargetPoint>(Actors[0])->GetActorLocation();*/
	

	//central_point_location = crunch->target_location;
	//GetBlackboardComponent()->SetValueAsVector(FName("Return_to_locatiion"), central_point_location);
	if (UseBlackboard(blackboard_data, BlackboardComp)) {
		RunBehaviorTree(behaviortree);
	}

	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACrunch_ai_controller::Player_check, 0.5f, true);
	
	GetBlackboardComponent()->SetValueAsVector(FName("Return_to_location"), central_point_location);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACrunch_ai_controller::Player_check, 0.5f, true);
	
}

void ACrunch_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ACrunch_ai_controller::Player_check()
{
	TArray<FOverlapResult> overlap_result;
	FCollisionQueryParams QueryParams(NAME_None, false, crunch);

	bool bResult=crunch->GetWorld()->OverlapMultiByChannel(
		overlap_result,
		central_point_location,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(crunch->sensing_rad),
		QueryParams);

	if (bResult==true) {
		int index = FMath::RandRange(0, overlap_result.Num()-1);
		GetBlackboardComponent()->SetValueAsObject(FName("Shooter_to_Attack"), Cast<ATPS_Shooter>(overlap_result[index].GetActor()));
		DrawDebugSphere(crunch->GetWorld(), central_point_location, crunch->sensing_rad, 16, FColor::Red, false, 0.1f);
	}
	else if(bResult == false) {
		GetBlackboardComponent()->SetValueAsObject(FName("Shooter_to_Attack"), nullptr);
		DrawDebugSphere(crunch->GetWorld(), central_point_location, crunch->sensing_rad, 16, FColor::Green, false, 0.1f);
	}


}

void ACrunch_ai_controller::First_initialize_position()
{
	TArray<FOverlapResult> overlap_result;
	FCollisionQueryParams QueryParams(NAME_None, false, crunch);

	bool bResult = crunch->GetWorld()->OverlapMultiByChannel(
		overlap_result,
		crunch->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel9,
		FCollisionShape::MakeSphere(crunch->sensing_rad),
		QueryParams);

	if (bResult == true) {
		central_point_location = overlap_result[0].GetActor()->GetActorLocation();

	}
	else if (bResult == false) {
		
	}
}
