// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "FinalFPSGameMode.generated.h"

UCLASS(minimalapi)
class AFinalFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFinalFPSGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

};
