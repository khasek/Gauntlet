/*******************************************************************************
* GauntletPlayerState provides persistent (across levels) storage for
* player game states (current health and score, inventory contents, etc).
*
* Author: Kendal Hasek
*******************************************************************************/

#include "GauntletPlayerState.h"

/// <summary>
/// Read the player's current health
/// </summary>
/// <returns>The player's current health</returns>
const int AGauntletPlayerState::GetCurrentHealth() const
{
	return currentHealth;
}

/// <summary>
/// Read the player's current score
/// </summary>
/// <returns>The player's current score</returns>
const int AGauntletPlayerState::GetCurrentScore() const
{
	return currentScore;
}

/// <summary>
/// Read the player's current number of held keys
/// </summary>
/// <returns>The number of keys the player currently holds</returns>
const int AGauntletPlayerState::GetCurrentKeys() const
{
	return currentNumKeys;
}

/// <summary>
/// Read the player's current number of held potions
/// </summary>
/// <returns>The number of potions the player currently holds</returns>
const int AGauntletPlayerState::GetCurrentPotions() const
{
	return currentNumPotions;
}

/// <summary>
/// Update the player's current health
/// </summary>
/// <param name="amount">The amount of health gained or lost</param>
void AGauntletPlayerState::UpdateHealth(int amount)
{
	currentHealth += amount;
}

/// <summary>
/// Increase the player's current score
/// </summary>
/// <param name="amount">The number of points earned</param>
void AGauntletPlayerState::IncreaseScore(int amount)
{
	currentScore += amount;
}

/// <summary>
/// Increment the number of keys the player is holding
/// </summary>
void AGauntletPlayerState::AddKey()
{
	currentNumKeys++;
}

/// <summary>
/// Decrement the number of keys the player is holding
/// </summary>
void AGauntletPlayerState::RemoveKey()
{
	currentNumKeys--;
}

/// <summary>
/// Increment the number of potions the player is holding
/// </summary>
void AGauntletPlayerState::AddPotion()
{
	currentNumPotions++;
}

/// <summary>
/// Decrement the number of potions the player is holding
/// </summary>
void AGauntletPlayerState::RemovePotion()
{
	currentNumPotions--;
}
