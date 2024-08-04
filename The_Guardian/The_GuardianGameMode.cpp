// Copyright Epic Games, Inc. All Rights Reserved.

#include "The_GuardianGameMode.h"
#include "The_GuardianCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThe_GuardianGameMode::AThe_GuardianGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
