// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalFPSGameMode.h"
#include "FinalFPSCharacter.h"
#include "PersistencePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AFinalFPSGameMode::AFinalFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AFinalFPSGameMode::PostLogin(APlayerController* NewPlayer)
{
	//Super::PostLogin(NewPlayer);

	if (APersistencePlayerController* PC = Cast<APersistencePlayerController>(NewPlayer)) {
		PC->ServerEntryHandler();
	}
}
