// Fill out your copyright notice in the Description page of Project Settings.


#include "Set_Player_location.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPS_Shooter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
//#include "TPS_Shooter.h"
USet_Player_location::USet_Player_location()
{
	NodeName = TEXT("Reset_player_position");
	Interval = 0.2f;
}

void USet_Player_location::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	player = Cast<ATPS_Shooter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Shooter_to_Attack")));
	if (player == nullptr) {
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Shooter_location"), player->GetActorLocation());
}
