// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBaseClass.h"

// Sets default values
APlayerCharacterBaseClass::APlayerCharacterBaseClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacterBaseClass::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacterBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterBaseClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &APlayerCharacterBaseClass::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APlayerCharacterBaseClass::MoveLeftRight);
}

void APlayerCharacterBaseClass::MoveForwardBack(float value) 
{
	AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacterBaseClass::MoveLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void APlayerCharacterBaseClass::Shoot()
{

}

void APlayerCharacterBaseClass::UsePotion()
{

}

