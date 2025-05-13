// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelector.h"

// Sets default values
ACharacterSelector::ACharacterSelector()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterSelector::BeginPlay()
{
	Super::BeginPlay();

	currentWidgetIndex = 0;

}

// Called to bind functionality to input
void ACharacterSelector::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("NextCharacter", IE_Pressed, this, &ACharacterSelector::NextCharacter);
	PlayerInputComponent->BindAction("PrevCharacter", IE_Pressed, this, &ACharacterSelector::PrevCharacter);
	PlayerInputComponent->BindAction("SelectCharacter", IE_Pressed, this, &ACharacterSelector::SelectCharacter);
}

void ACharacterSelector::NextCharacter()
{
	
}

void ACharacterSelector::PrevCharacter()
{

}

void ACharacterSelector::SelectCharacter()
{

}
