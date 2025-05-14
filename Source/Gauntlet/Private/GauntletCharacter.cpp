/*******************************************************************************
* GauntletCharacter is the base class for the four playable characters:
* Warrior, Valkyrie, Wizard, and Elf.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "GauntletCharacter.h"

AGauntletCharacter::AGauntletCharacter()
{
 	
}

// Called when the game starts or when spawned
void AGauntletCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AGauntletCharacter::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AGauntletCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis("Shoot", this, &AGauntletCharacter::Shoot);
	PlayerInputComponent->BindAction("UsePotion", IE_Pressed, this, &AGauntletCharacter::UsePotion);
}

void AGauntletCharacter::MoveForwardBack(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AGauntletCharacter::MoveLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AGauntletCharacter::Shoot(float value)
{

}

void AGauntletCharacter::UsePotion()
{

}