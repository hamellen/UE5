// Fill out your copyright notice in the Description page of Project Settings.


#include "player_position_capture.h"
#include "Monster_AIController.h"
#include "Playerable_char.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

Uplayer_position_capture::Uplayer_position_capture()
{
	NodeName = TEXT("Player_position_capture");
	Interval = 0.5f;
	capture_range = 1000.f;
}

void Uplayer_position_capture::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (currentPawn==nullptr) {
		return;
	}

	UWorld* world = currentPawn->GetWorld();
	TArray<FOverlapResult> Overlapresults;
	FCollisionQueryParams Params(NAME_None, false, currentPawn);


	bool bResult=world->OverlapMultiByChannel(Overlapresults, currentPawn->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeSphere(capture_range), Params);

	if (bResult) {

		for (auto& overlap : Overlapresults) {
			APlayerable_char* player = Cast<APlayerable_char>(overlap.GetActor());
			if (player) {
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Player_current_position"), player->GetActorLocation());
			}
		}

	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Player_current_position"),FVector(0.f,0.f,0.f) );
	}
	
}
