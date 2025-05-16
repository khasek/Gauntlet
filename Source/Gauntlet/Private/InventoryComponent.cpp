/*******************************************************************************
* InventoryComponent manages inventory space for player characters.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

/// <summary>
/// Add a key to the inventory, if there's space
/// </summary>
/// <returns>True if the key was successfully added</returns>
bool UInventoryComponent::AddKey()
{
	if ((numKeys + numPotions) < maxItems)
	{
		numKeys++;
		NumKeysChanged.Broadcast(playerCharacter, numKeys);
		return true;
	}
	return false;
}

/// <summary>
/// Remove a key from the inventory
/// </summary>
/// /// <returns>True if there were any keys to remove</returns>
bool UInventoryComponent::RemoveKey()
{
	if (numKeys > 0)
	{
		numKeys--;
		NumKeysChanged.Broadcast(playerCharacter, numKeys);
		return true;
	}
	return false;
}

/// <summary>
/// Set the number of keys in the inventory, up to the number of
/// currently available slots.
/// </summary>
/// <param name="amount">Number of keys</param>
void UInventoryComponent::SetKeys(int amount)
{
	int maxKeys = maxItems - numPotions;
	numKeys = FMath::Min(amount, maxKeys);
	NumKeysChanged.Broadcast(playerCharacter, numKeys);
}

/// <summary>
/// Add a potion to the inventory, if there's space
/// </summary>
/// <returns>True if a potion was successfully added</returns>
bool UInventoryComponent::AddPotion()
{
	if ((numKeys + numPotions) < maxItems)
	{
		numPotions++;
		NumPotionsChanged.Broadcast(playerCharacter, numPotions);
		return true;
	}
	return false;
}

/// <summary>
/// Remove a potion from the inventory
/// </summary>
/// /// <returns>True if there were any potions to remove</returns>
bool UInventoryComponent::RemovePotion()
{
	if (numPotions > 0)
	{
		numPotions--;
		NumPotionsChanged.Broadcast(playerCharacter, numPotions);
		return true;
	}
	return false;
}

/// <summary>
/// Set the number of potions in the inventory, up to the number of
/// currently available slots
/// </summary>
/// <param name="amount">Number of potions</param>
void UInventoryComponent::SetPotions(int amount)
{
	int maxPotions = maxItems - numKeys;
	numPotions = FMath::Min(amount, maxPotions);
	NumPotionsChanged.Broadcast(playerCharacter, numPotions);
}
