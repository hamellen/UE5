// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMoveFinding.h"
#include "NavigationSystem.h"
#include "Monster_AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTTask_RandomMoveFinding::UBTTask_RandomMoveFinding()
{
	NodeName = TEXT("RamdomMovePositionFinding");

	random_range = 600.f;
}

EBTNodeResult::Type UBTTask_RandomMoveFinding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Ownpawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Ownpawn == nullptr) {
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* navsystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (!navsystem) {
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;

	if (navsystem->GetRandomPointInNavigableRadius(Ownpawn->GetActorLocation(), random_range, RandomLocation)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandomMovePosition")), RandomLocation.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
