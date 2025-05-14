/*******************************************************************************
* GauntletPlayerState provides persistent (across levels) storage for
* player game states (current health and score, inventory contents, etc).
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GauntletPlayerState.generated.h"

UCLASS()
class GAUNTLET_API AGauntletPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	const int GetCurrentHealth() const;
	const int GetCurrentScore() const;
	const int GetCurrentKeys() const;
	const int GetCurrentPotions() const;

	void UpdateHealth(int amount);
	void IncreaseScore(int amount);
	void AddKey();
	void RemoveKey();
	void AddPotion();
	void RemovePotion();

private:
	int currentHealth;
	int currentScore;
	int currentNumKeys;
	int currentNumPotions;
};
