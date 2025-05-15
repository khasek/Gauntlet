/*******************************************************************************
* GauntletGameInstance maintains a persistent record of which players are
* playing which characters.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GauntletGameInstance.generated.h"


UCLASS()
class GAUNTLET_API UGauntletGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	const TMap<FName, int>& GetCharacterAssignmentMap() const;
	TArray<FString> GetAssignedPlayers();
	bool AddCharacterAssignment(FName, int);

private:
	TMap<FName, int> CharacterAssignments;
	TMap<int, FName> AssignedCharacters;
};
