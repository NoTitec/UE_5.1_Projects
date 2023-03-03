// Copyright Epic Games, Inc. All Rights Reserved.

#include "MT01GameMode.h"
#include "MT01Character.h"
#include "UObject/ConstructorHelpers.h"

AMT01GameMode::AMT01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
