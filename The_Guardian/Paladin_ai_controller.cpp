// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin_ai_controller.h"
#include "NavigationSystem.h"
#include "Paladin.h"
#include "TPS_Shooter.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
APaladin_ai_controller::APaladin_ai_controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("/Script/AIModule.BlackboardData'/Game/Monster/Paladin/BB_Paladin.BB_Paladin'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/Paladin/BT_Paladin.BT_Paladin'"));

	if (BD.Succeeded()) {
		blackboard_data = BD.Object;
	}

	if (BT.Succeeded()) {
		behaviortree = BT.Object;
	}
}

void APaladin_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;

	paladin = Cast<APaladin>(GetPawn());

	if (UseBlackboard(blackboard_data, BlackboardComp)) {
		RunBehaviorTree(behaviortree);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APaladin_ai_controller::Player_check, 0.5f, true);
}

void APaladin_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();


	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void APaladin_ai_controller::Player_check()
{
	GetBlackboardComponent()->SetValueAsBool(FName("is_active"),paladin->is_active );

	TArray<FOverlapResult> overlap_result;
	FCollisionQueryParams QueryParams(NAME_None, false, paladin);

	bool bResult = paladin->GetWorld()->OverlapMultiByChannel(
		overlap_result,
		paladin->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(paladin->sensing_rad),
		QueryParams);

	if (bResult == true) {
		int index = FMath::RandRange(0, overlap_result.Num() - 1);
		GetBlackboardComponent()->SetValueAsObject(FName("Player_to_attack"), Cast<ATPS_Shooter>(overlap_result[index].GetActor()));
		DrawDebugSphere(paladin->GetWorld(), paladin->GetActorLocation(), paladin->sensing_rad, 16, FColor::Red, false, 0.1f);
		paladin->is_targeted = true;
	}
	else if (bResult == false) {
		GetBlackboardComponent()->SetValueAsObject(FName("Player_to_attack"), nullptr);
		DrawDebugSphere(paladin->GetWorld(), paladin->GetActorLocation(), paladin->sensing_rad, 16, FColor::Green, false, 0.1f);
		paladin->is_targeted = false;
	}
}
