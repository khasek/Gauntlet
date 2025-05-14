/*******************************************************************************
* StartupGameMode spawns controllers for multiplayer and manages the transition
* from character selection to Level 1.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GauntletPlayerController.h"
#include "StartupGameMode.generated.h"

UCLASS()
class GAUNTLET_API AStartupGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStartupGameMode();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

private:
	TArray<AGauntletPlayerController*> players;
};
