// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabaEdition3GameMode.h"
#include "LabaEdition3Character.h"
#include "UObject/ConstructorHelpers.h"

ALabaEdition3GameMode::ALabaEdition3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
