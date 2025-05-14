// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "GauntletPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, AGauntletPlayerController*, playerController);

UCLASS()
class GAUNTLET_API AGauntletPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void FreezeCharacterSelection();
	void SelectCharacter(FName character);

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnCharacterSelected Player0CharacterSelected;
};
