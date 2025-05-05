// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMovingCube.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ATestMovingCube::ATestMovingCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void ATestMovingCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestMovingCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ATestMovingCube::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ATestMovingCube::MoveLeftRight);
}

void ATestMovingCube::MoveForwardBack(float value)
{
	// If this Pawn is possessed by a Controller and the input value is nonzero, move
	if (Controller && value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ATestMovingCube::MoveLeftRight(float value)
{
	// If this Pawn is possessed by a Controller and the input value is nonzero, move
	if (Controller && value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}