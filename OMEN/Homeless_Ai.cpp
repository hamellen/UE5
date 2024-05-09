// Fill out your copyright notice in the Description page of Project Settings.


#include "Homeless_Ai.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "homeless_ch.h"



AHomeless_Ai::AHomeless_Ai()
{

}

void AHomeless_Ai::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AHomeless_Ai::homeless_move()
{
	
	UE_LOG(LogTemp, Warning, TEXT("homeless_move"));

	//UNavigationSystemV1* navsystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());


	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, FVector(-3312.730403, -11295.906811, 104.493537));
}
