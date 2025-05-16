/*******************************************************************************
* InventoryComponent manages inventory space for player characters.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKeyUpdate, FString, character, int, currentKeys);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPotionUpdate, FString, character, int, currentPotions);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	bool AddKey();
	bool RemoveKey();
	void SetKeys(int amount);

	bool AddPotion();
	bool RemovePotion();
	void SetPotions(int amount);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKeyUpdate NumKeysChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPotionUpdate NumPotionsChanged;

protected:
	virtual void BeginPlay() override;

	FString playerCharacter; // Warrior, etc.
	int maxItems = 12;
	int numKeys = 0;
	int numPotions = 0;
};
