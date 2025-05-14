/*******************************************************************************
* GauntletGameInstance maintains a persistent record of which players are
* playing which characters.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GauntletPlayerController.h"
#include "GauntletGameInstance.generated.h"


UCLASS()
class GAUNTLET_API UGauntletGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	const TMap<FName, AGauntletPlayerController*>& GetCharacterAssignments() const;
	bool AddCharacterAssignment(FName, AGauntletPlayerController*);

private:
	TMap<FName, AGauntletPlayerController*> CharacterAssignments;
	TMap<AGauntletPlayerController*, FName> AssignedCharacters;

};
