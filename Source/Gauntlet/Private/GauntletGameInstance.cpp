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

	CharacterAssignments.Add(TEXT("Warrior"), nullptr);
	CharacterAssignments.Add(TEXT("Valkyrie"), nullptr);
	CharacterAssignments.Add(TEXT("Wizard"), nullptr);
	CharacterAssignments.Add(TEXT("Elf"), nullptr);
}

/// <summary>
/// A read-only request for character assignment information
/// </summary>
/// <returns>A constant reference to the map of character assignments</returns>
const TMap<FName, APlayerController*>& UGauntletGameInstance::GetCharacterAssignments() const
{
	return CharacterAssignments;
}

/// <summary>
/// Assign a player to a character class
/// </summary>
/// <param name="character">A character class name (Warrior, Valkyrie, Wizard, Elf)</param>
/// <param name="player">The PlayerController that wants the character</param>
/// <returns>A boolean indicating whether the assignment was successful</returns>
bool UGauntletGameInstance::AddCharacterAssignment(FName character, APlayerController* player)
{
	// If the requested character is already claimed return false
	if (CharacterAssignments[character] != nullptr)
	{
		return false;
	}

	// Player has not already been assigned to a character
	if (!AssignedCharacters.Contains(player))
	{
		AssignedCharacters.Add(player, character);
		CharacterAssignments[character] = player;
		return true;
	}

	FName previousCharacter = AssignedCharacters[player];
	AssignedCharacters[player] = character;
	CharacterAssignments[character] = player;
	CharacterAssignments[previousCharacter] = nullptr;
	return true;
}
