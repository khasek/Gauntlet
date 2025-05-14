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

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	int32 PlayerIndex = PC->GetLocalPlayer()->GetControllerId();

	switch (PlayerIndex)
	{
	case 0:
		PlayerInputComponent->BindAction("Shoot_P1", IE_Pressed, this, &APlayerCharacterBaseClass::Shoot);
		break;

	case 1:
		PlayerInputComponent->BindAction("Shoot_P2", IE_Pressed, this, &APlayerCharacterBaseClass::Shoot);
		break;

	case 2:
		PlayerInputComponent->BindAction("Shoot_P3", IE_Pressed, this, &APlayerCharacterBaseClass::Shoot);
		break;

	case 3:
		PlayerInputComponent->BindAction("Shoot_P3", IE_Pressed, this, &APlayerCharacterBaseClass::Shoot);
		break;

	default:
		break;
	}
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
	//AActor* Owner = GetOwner();
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	APlayerProjectile* Projectile = GetWorld()->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	FVector Dir = GetActorForwardVector();
	Projectile->Init(Dir);
}

void APlayerCharacterBaseClass::UsePotion()
{

}


