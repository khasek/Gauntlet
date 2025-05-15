/*******************************************************************************
* GauntletGameInstance maintains a persistent record of which players are
* playing which characters.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "GauntletGameInstance.h"

/// <summary>
/// Initialize the character assignments map on startup
/// </summary>
void UGauntletGameInstance::Init()
{
	Super::Init();

	CharacterAssignments.Add(FName("Warrior"), -1);
	CharacterAssignments.Add(FName("Valkyrie"), -1);
	CharacterAssignments.Add(FName("Wizard"), -1);
	CharacterAssignments.Add(FName("Elf"), -1);
}

/// <summary>
/// A read-only request for character assignment information
/// </summary>
/// <returns>A constant reference to the map of character assignments</returns>
const TMap<FName, int>& UGauntletGameInstance::GetCharacterAssignmentMap() const
{
	return CharacterAssignments;
}

/// <summary>
/// Returns a formatted list of players that have been assigned to characters 
/// in the order Warrior, Valkyrie, Wizard, Elf
/// </summary>
/// <returns>Formatted player ID strings (like P0)</returns>
TArray<FString> UGauntletGameInstance::GetAssignedPlayers()
{
	TArray<FString> playerIDs = {};
	for (auto& pair : CharacterAssignments)
	{
		if (pair.Value == -1)
		{
			playerIDs.Add("");
		}
		else
		{
			playerIDs.Add("P" + FString::FromInt(pair.Value));
		}
	}

	return playerIDs;
}

/// <summary>
/// Assign a player to a character class
/// </summary>
/// <param name="character">A character class name (Warrior, Valkyrie, Wizard, Elf)</param>
/// <param name="player">The ID of the player that wants the character</param>
/// <returns>A boolean indicating whether the assignment was successful</returns>
bool UGauntletGameInstance::AddCharacterAssignment(FName character, int player)
{
	// If the requested character is nonexistent or already claimed return false
	if (!CharacterAssignments.Find(character) || CharacterAssignments[character] != -1)
	{
		return false;
	}

	// Player is choosing a character for the first time
	if (!AssignedCharacters.Contains(player))
	{
		AssignedCharacters.Add(player, character);
		CharacterAssignments[character] = player;
		return true;
	}

	// Player needs to be reassigned
	FName previousCharacter = AssignedCharacters[player];
	AssignedCharacters[player] = character;
	CharacterAssignments[character] = player;
	CharacterAssignments[previousCharacter] = -1;
	return true;
}
