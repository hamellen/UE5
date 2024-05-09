
// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
AMonster_AIController::AMonster_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("BlackboardData'/Game/Monster_AI/Monster_BB.Monster_BB'"));
	if (BD.Succeeded()) {
		blackboard_data = BD.Object;
	}
		
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/Monster_AI/Monster_BT.Monster_BT'"));
	if (BT.Succeeded()) {
		behaviortree = BT.Object;
	}

}

void AMonster_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	

	
	
	UBlackboardComponent* BlackboardComp = Blackboard;
	//BlackboardComp->SetValueAsBool(FName("Is_sound_trace"), false);//bool값 초기 설정
	//BlackboardComp->SetValueAsBool(FName("Is_counter_attack"), false);//bool값 초기 설정
	if (UseBlackboard(blackboard_data, BlackboardComp)) {
		RunBehaviorTree(behaviortree);
	}

}

void AMonster_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMonster_AIController::activate_sound_trace()
{
	UE_LOG(LogTemp, Warning, TEXT("sound trace start"));
	FVector moveto_origin = GetBlackboardComponent()->GetValueAsVector(FName("Player_current_position"));
	GetBlackboardComponent()->SetValueAsVector(FName("sound_origin"), moveto_origin);
	GetBlackboardComponent()->SetValueAsBool(FName("Is_sound_trace"), true);

}




void AMonster_AIController::Reset_mode()
{
	
	GetBlackboardComponent()->SetValueAsBool(FName("Is_sound_trace"), false);//bool값 초기 설정
	GetBlackboardComponent()->SetValueAsBool(FName("Is_counter_attack"), false);//bool값 초기 설정
	dele_end.Broadcast();

}

void AMonster_AIController::activate_counter()
{
	GetBlackboardComponent()->SetValueAsBool(FName("Is_counter_attack"), true);
	
}


