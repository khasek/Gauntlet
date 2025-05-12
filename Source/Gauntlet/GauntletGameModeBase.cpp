// Copyright Epic Games, Inc. All Rights Reserved.


#include "GauntletGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void AGauntletGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Set up the top-down camera view -----------------------------------------

	// Get a reference to the game camera
	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainCamera"), cameras);

	if (cameras.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No camera with tag 'MainCamera' found."));
		return;
	}

	AActor* mainCamera = cameras[0];

	// Get references to all active player pawns
	TArray<AActor*> playerPawns;
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

	// Calculate midpoint of all player pawns
	FVector sum = FVector::ZeroVector;
	for (AActor* player : playerPawns)
	{
		sum += player->GetActorLocation();
	}

	FVector midpoint = sum / playerPawns.Num();

	// Update camera position to follow midpoint
	FVector cameraZOffset = FVector(0, 0, 2000);
	mainCamera->SetActorLocation(midpoint + cameraZOffset);

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
