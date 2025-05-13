// Copyright Epic Games, Inc. All Rights Reserved.


#include "GauntletGameModeBase.h"
#include "GauntletPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "CameraManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void AGauntletGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Initialize player controllers -------------------------------------------

	// Override default new player handling
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AGauntletPlayerController::StaticClass();

	// Set up the top-down camera view -----------------------------------------

	// Get a reference to the game camera
	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainCamera"), cameras);

	if (cameras.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No camera with tag 'MainCamera' found."));
		return;
	}

	ACameraManager* mainCamera = Cast<ACameraManager>(cameras[0]);

	// Get references to all active player pawns
	for (int i = 0; i < 4; i++)
	{
		APawn* pawn = UGameplayStatics::GetPlayerPawn(this, i);
		if (pawn)
		{
			playerPawns.Add(pawn);
		}
	}

	if (playerPawns.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player pawns found."));
		return;
	}

	// Send the camera a reference to the players
	mainCamera->SetPlayerTargets(playerPawns);

	// Set all players' view targets to this camera
	for (int i = 0; i < playerPawns.Num(); i++)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, i);
		if (playerController)
		{
			playerController->SetViewTarget(mainCamera);
		}
	}

}
