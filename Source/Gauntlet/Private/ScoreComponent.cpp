/*******************************************************************************
* ScoreComponent handles player score updates
*
* Author: Kendal Hasek
*******************************************************************************/

#include "ScoreComponent.h"


UScoreComponent::UScoreComponent()
{

}

/// <summary>
/// Update the player's score
/// </summary>
/// <param name="amount">New points to add</param>
void UScoreComponent::IncreaseScore(int amount)
{
	score += amount;
	ScoreUpdated.Broadcast(playerCharacter, score);
	UE_LOG(LogTemp, Warning, TEXT("Player score increased! Score is now %d"), score);
}
