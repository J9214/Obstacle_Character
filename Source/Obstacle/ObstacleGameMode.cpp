// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObstacleGameMode.h"
#include "ObstacleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AObstacleGameMode::AObstacleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
