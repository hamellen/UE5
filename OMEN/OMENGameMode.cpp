// Copyright Epic Games, Inc. All Rights Reserved.

#include "OMENGameMode.h"
#include "OMENCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOMENGameMode::AOMENGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	/*if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
