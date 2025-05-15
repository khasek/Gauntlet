/*******************************************************************************
* MainGameMode handles the initial setup for each level.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "CameraManager.h"
#include "GauntletGameInstance.h"
#include "GauntletPlayerState.h"
#include "GauntletPlayerController.h"
#include "GauntletCharacter.h"
#include "MainGameMode.h"

AMainGameMode::AMainGameMode()
{
	PlayerControllerClass = AGauntletPlayerController::StaticClass();
	PlayerStateClass = AGauntletPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
	bUseSeamlessTravel = true;

	// Get a reference to each playable character blueprint
	static ConstructorHelpers::FClassFinder<AGauntletCharacter> Warrior(TEXT("/Game/Blueprints/BP_Warrior"));
	WarriorReference = Warrior.Class;

	static ConstructorHelpers::FClassFinder<AGauntletCharacter> Valkyrie(TEXT("/Game/Blueprints/BP_Valkyrie"));
	ValkyrieReference = Valkyrie.Class;

	static ConstructorHelpers::FClassFinder<AGauntletCharacter> Wizard(TEXT("/Game/Blueprints/BP_Wizard"));
	WizardReference = Wizard.Class;

	static ConstructorHelpers::FClassFinder<AGauntletCharacter> Elf(TEXT("/Game/Blueprints/BP_Elf"));
	ElfReference = Elf.Class;
}

/// <summary>
/// Spawn players and set up the camera. PostSeamlessTravel is like BeginPlay,
/// except it delays timing slightly to allow for things from the previous level
/// to get ready.
/// </summary>
void AMainGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();

	UE_LOG(LogTemp, Warning, TEXT("In PostSeamlessTravel"));

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
		UE_LOG(LogTemp, Warning, TEXT("Not enough PlayerStarts, setting default spawn locations"));

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
		UE_LOG(LogTemp, Warning, TEXT("Getting PlayerStart transforms"));

		for (AActor* marker : spawnMarkers)
		{
			spawnTransforms.Add(marker->GetActorTransform());
		}
	}

	// Get character:player pairs
	UGauntletGameInstance* gameInstance = Cast<UGauntletGameInstance>(GetGameInstance());
	const TMap<FName, int> characterAssignments = gameInstance->GetCharacterAssignmentMap();

	// Spawn Warrior
	if (characterAssignments["Warrior"] != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Gauntlet pawn"));
		AGauntletCharacter* warrior = GetWorld()->SpawnActor<AGauntletCharacter>(WarriorReference, spawnTransforms[0]);
		APlayerController* warriorController = UGameplayStatics::GetPlayerController(GetWorld(), characterAssignments["Warrior"]);
		warriorController->Possess(warrior);
		warriorController->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(warrior);
	}

	// Spawn Valkyrie
	if (characterAssignments["Valkyrie"] != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Gauntlet pawn"));
		AGauntletCharacter* valkyrie = GetWorld()->SpawnActor<AGauntletCharacter>(ValkyrieReference, spawnTransforms[1]);
		APlayerController* valkyrieController = UGameplayStatics::GetPlayerController(GetWorld(), characterAssignments["Valkyrie"]);
		valkyrieController->Possess(valkyrie);
		valkyrieController->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(valkyrie);
	}

	// Spawn Wizard
	if (characterAssignments["Wizard"] != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Gauntlet pawn"));
		AGauntletCharacter* wizard = GetWorld()->SpawnActor<AGauntletCharacter>(WizardReference, spawnTransforms[2]);
		APlayerController* wizardController = UGameplayStatics::GetPlayerController(GetWorld(), characterAssignments["Wizard"]);
		wizardController->Possess(wizard);
		wizardController->SetViewTarget(mainCamera);
		mainCamera->AddPlayerTarget(wizard);
	}

	// Spawn Elf
	if (characterAssignments["Elf"] != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Gauntlet pawn"));
		AGauntletCharacter* elf = GetWorld()->SpawnActor<AGauntletCharacter>(ElfReference, spawnTransforms[3]);
		APlayerController* elfController = UGameplayStatics::GetPlayerController(GetWorld(), characterAssignments["Elf"]);
		elfController->Possess(elf);
		elfController->SetViewTarget(mainCamera);
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
