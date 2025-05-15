/*******************************************************************************
* MainGameMode handles the initial setup for each level.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GauntletCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class GAUNTLET_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainGameMode();
	virtual void PostSeamlessTravel() override;

	UFUNCTION(BlueprintCallable)
	void NextLevel(FName levelName);

private:
	TSubclassOf<AGauntletCharacter> WarriorReference;
	TSubclassOf<AGauntletCharacter> ValkyrieReference;
	TSubclassOf<AGauntletCharacter> WizardReference;
	TSubclassOf<AGauntletCharacter> ElfReference;
};
