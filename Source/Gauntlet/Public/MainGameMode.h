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
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void NextLevel(FName levelName);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGauntletCharacter> WarriorReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGauntletCharacter> ValkyrieReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGauntletCharacter> WizardReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGauntletCharacter> ElfReference;

};
