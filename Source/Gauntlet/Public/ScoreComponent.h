/*******************************************************************************
* ScoreComponent handles player score updates
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdate, FString, character, int, newScore);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScoreComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnScoreUpdate ScoreUpdated;

	void IncreaseScore(int amount);

protected:
	FString playerCharacter; // Warrior, etc.
	int score;
};
