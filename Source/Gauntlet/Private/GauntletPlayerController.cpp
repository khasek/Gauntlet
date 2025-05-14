// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GauntletPlayerController.h"

void AGauntletPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AGauntletPlayerController::FreezeCharacterSelection()
{

}

void AGauntletPlayerController::SelectCharacter(FName character)
{
	// Character selection logic

	// UI button will be listening for Player 0 to choose a character before enabling itself
	if (UGameplayStatics::GetPlayerControllerID(this) == 0)
	{
		Player0CharacterSelected.Broadcast(this);
	}
}