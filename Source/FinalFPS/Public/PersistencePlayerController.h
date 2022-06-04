// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Http.h"
#include "PersistencePlayerController.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData {
	GENERATED_BODY()
	UPROPERTY()
	bool isvalid = false;
	UPROPERTY()
	int pid = -1;
	UPROPERTY()
	FString playername;
};

UCLASS()
class FINALFPS_API APersistencePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APersistencePlayerController();

	virtual void BeginPlay() override;

	void ServerEntryHandler();

protected:
	FHttpModule* Http;
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	FPlayerData ConvertToPData(const FString& ResponseString);
};
