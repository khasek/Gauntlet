/*******************************************************************************
* MainGameMode handles the initial setup for each level.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "CameraManager.h"
#include "GauntletGameInstance.h"
#include "GauntletPlayerController.h"
#include "GauntletCharacter.h"
#include "MainGameMode.h"

/// <summary>
/// Spawn players and set up the camera
/// </summary>
void AMainGameMode::BeginPlay()
{
	// Get a reference to the game camera
	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainCamera"), cameras);

	if (cameras.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No camera with tag 'MainCamera' found."));
		return;
	}

	ACameraManager* mainCamera = Cast<ACameraManager>(cameras[0]);

	// Get starting locations/transforms
	TArray<AActor*> spawnMarkers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), spawnMarkers);

	TArray<FTransform> spawnTransforms;
	if (spawnMarkers.Num() < 4)
	{
		// Set default spawnMarkers in the middle of the map
		spawnTransforms = {
			FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(100.0f, 0.0f, 0.0f)),
			FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 100.0f, 0.0f)),
			FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(-100.0f, 0.0f, 0.0f)),
			FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, -100.0f, 0.0f))
		};
	}
	else
	{
		for (AActor* marker : spawnMarkers)
		{
			spawnTransforms.Add(marker->GetActorTransform());
		}
	}

	// Get character:player pairs
	UGauntletGameInstance* gameInstance = Cast<UGauntletGameInstance>(GetGameInstance());
	const TMap<FName, AGauntletPlayerController*> characterAssignments = gameInstance->GetCharacterAssignments();

	// Spawn Warrior
	if (characterAssignments["Warrior"] != nullptr)
	{
		AGauntletCharacter* warrior = GetWorld()->SpawnActor<AGauntletCharacter>(WarriorReference, spawnTransforms[0]);
		characterAssignments["Warrior"]->Possess(warrior);
		characterAssignments["Warrior"]->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(warrior);
	}

	// Spawn Valkyrie
	if (characterAssignments["Valkyrie"] != nullptr)
	{
		AGauntletCharacter* valkyrie = GetWorld()->SpawnActor<AGauntletCharacter>(ValkyrieReference, spawnTransforms[1]);
		characterAssignments["Valkyrie"]->Possess(valkyrie);
		characterAssignments["Valkyrie"]->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(valkyrie);
	}

	// Spawn Wizard
	if (characterAssignments["Wizard"] != nullptr)
	{
		AGauntletCharacter* wizard = GetWorld()->SpawnActor<AGauntletCharacter>(WizardReference, spawnTransforms[2]);
		characterAssignments["Wizard"]->Possess(wizard);
		characterAssignments["Wizard"]->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(wizard);
	}

	// Spawn Elf
	if (characterAssignments["Elf"] != nullptr)
	{
		AGauntletCharacter* elf = GetWorld()->SpawnActor<AGauntletCharacter>(ElfReference, spawnTransforms[3]);
		characterAssignments["Elf"]->Possess(elf);
		characterAssignments["Elf"]->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(elf);
	}
}

/// <summary>
/// Load the next level
/// </summary>
void AMainGameMode::NextLevel(FName levelName)
{
	UGameplayStatics::OpenLevel(this, levelName, true);
}
