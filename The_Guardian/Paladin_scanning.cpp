// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin_scanning.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPS_Shooter.h"
#include "Paladin.h"
#include "Paladin_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
UPaladin_scanning::UPaladin_scanning()
{
	NodeName = TEXT("Paladin_scaning");
	Interval = 0.2f;

}

void UPaladin_scanning::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	paladin = Cast<APaladin>(OwnerComp.GetAIOwner()->GetPawn());
	player = Cast<ATPS_Shooter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Player_to_attack")));
	if (player == nullptr) {
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Shooter_location"), player->GetActorLocation());
	paladin->shooter_location = player->GetActorLocation();


}
