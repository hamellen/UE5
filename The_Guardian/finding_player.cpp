// Fill out your copyright notice in the Description page of Project Settings.


#include "finding_player.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPS_Shooter.h"
#include "Crunch.h"
#include "Crunch_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

Ufinding_player::Ufinding_player()
{
	NodeName = TEXT("finding player");
	Interval = 0.3f;
	
}



void Ufinding_player::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	crunch = Cast<ACrunch>(OwnerComp.GetAIOwner()->GetPawn());
	TArray<FOverlapResult> overlap_result;
	FCollisionQueryParams QueryParams(NAME_None, false, crunch);
	

	


	bool bResult = crunch->GetWorld()->OverlapMultiByChannel(
		overlap_result,
		crunch->target_location,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(crunch->sensing_rad),
		QueryParams);

	if (bResult == true) {
		int index = FMath::RandRange(0, overlap_result.Num() - 1);
		auto player=Cast<ATPS_Shooter>(overlap_result[index].GetActor());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Shooter_to_Attack")), player);
		DrawDebugSphere(crunch->GetWorld(), crunch->target_location, crunch->sensing_rad, 16, FColor::Red, false, 0.1f);
	}
	else if (bResult == false) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Shooter_to_Attack")), nullptr);
		DrawDebugSphere(crunch->GetWorld(), crunch->target_location, crunch->sensing_rad, 16, FColor::Green, false, 0.1f);
	}


}
