/*******************************************************************************
* GauntletPlayerController handles character selection logic. Once regular
* gameplay begins, it works just like any other PlayerController.
* 
* Author: Kendal Hasek
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "GauntletGameInstance.h"
#include "GauntletPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, const TArray<FString>&, orderedPlayerIDs);

UCLASS()
class GAUNTLET_API AGauntletPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void FreezeCharacterSelection();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterSelected CharacterSelected;

private:
	int playerID;
	UGauntletGameInstance* gameInstance;

	void SelectWarrior();
	void SelectValkyrie();
	void SelectWizard();
	void SelectElf();
};
