/*******************************************************************************
* StartupGameMode spawns controllers for multiplayer and manages the transition
* from character selection to Level 1.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "Kismet/GameplayStatics.h"
#include "GauntletPlayerState.h"
#include "StartupGameMode.h"

/// <summary>
/// Constructor sets the default class for spawned PlayerControllers and PlayerStates
/// </summary>
AStartupGameMode::AStartupGameMode()
{
	PlayerControllerClass = AGauntletPlayerController::StaticClass();
	PlayerStateClass = AGauntletPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
	bUseSeamlessTravel = true;

}

/// <summary>
/// Spawn PlayerControllers and populate an array of references
/// </summary>
void AStartupGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Store a reference to Player 0
	players.Add(Cast<AGauntletPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)));

	// Spawn and store references for 3 extra players
	for (int i = 1; i < 4; i++)
	{
		players.Add(Cast<AGauntletPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), i, true)));
	}
}

/// <summary>
/// Transition from the character selection screen to Level 1
/// </summary>
void AStartupGameMode::StartGame()
{
	// Lock in player character assignments
	for (AGauntletPlayerController* player : players)
	{
		player->FreezeCharacterSelection();
	}

	// Load Level 1
	//UGameplayStatics::OpenLevel(this, "Level1", true);
	GetWorld()->GetFirstPlayerController()->ClientTravel("Level1", TRAVEL_Relative, true);
}
