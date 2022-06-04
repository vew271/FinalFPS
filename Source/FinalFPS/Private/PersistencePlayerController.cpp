// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistencePlayerController.h"
#include "Http.h"
#include "JsonObjectConverter.h"
#include "FinalFPS/FinalFPSGameMode.h"

APersistencePlayerController::APersistencePlayerController()
{
	Http = &FHttpModule::Get();
}

void APersistencePlayerController::BeginPlay()
{
	if (!HasAuthority()) {
		UE_LOG(LogTemp, Warning, TEXT("Running on Client"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Running on Server"));
	}
}

void APersistencePlayerController::ServerEntryHandler()
{
	if (!HasAuthority()) {
		return;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &APersistencePlayerController::OnProcessRequestComplete);
	Request->SetURL("http://localhost:8080/api/PlayerData/1234");
	Request->SetVerb("GET");
	//Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");

	/*FString JsonString;
	FPlayerData PlayerData;
	PlayerData.isvalid = true;
	PlayerData.playername = "Bobi";
	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, JsonString);
	Request->SetContentAsString(JsonString);*/

	//Get Request passing PID

	Request->ProcessRequest();
}

void APersistencePlayerController::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	FVector SpawnLoc = FVector::ZeroVector;
	SpawnLoc.Z = 400.0f;

	if (Success) {
		
		UE_LOG(LogTemp, Warning, TEXT("Success %s"), *Response->GetContentAsString());

		FPlayerData PlayerData = ConvertToPData(Response->GetContentAsString());
		if (PlayerData.isvalid) {
			UE_LOG(LogTemp, Warning, TEXT("Success %d"), PlayerData.pid);
			SpawnLoc.X = 400.0f;
			SpawnLoc.Y = 400.0f;
			SpawnLoc.Z = 400.0f;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("FAILED"));
	}

	//SpawnPawn
	if (AFinalFPSGameMode* GM = GetWorld()->GetAuthGameMode<AFinalFPSGameMode>()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (APawn* NewPawn = GetWorld()->SpawnActor<APawn>(GM->DefaultPawnClass, SpawnLoc, FRotator::ZeroRotator, SpawnParams)) {
			Possess(NewPawn);
		}
	}
}

FPlayerData APersistencePlayerController::ConvertToPData(const FString& ResponseString)
{
	FPlayerData PlayerData;
	if (!ResponseString.Contains("timestamp")) {
		FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &PlayerData, 0, 0);
	}

	return PlayerData;
}
