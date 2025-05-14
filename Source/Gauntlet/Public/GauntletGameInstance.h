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
	const TMap<FName, APlayerController*>& GetCharacterAssignments() const;
	bool AddCharacterAssignment(FName, APlayerController*);

private:
	TMap<FName, APlayerController*> CharacterAssignments;
	TMap<APlayerController*, FName> AssignedCharacters;

};
