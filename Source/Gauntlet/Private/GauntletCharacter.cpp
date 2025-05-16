/*******************************************************************************
* GauntletCharacter is the base class for the four playable characters:
* Warrior, Valkyrie, Wizard, and Elf.
*
* Author: Kendal Hasek, Logan Sharkey
*******************************************************************************/

#include "GauntletCharacter.h"

AGauntletCharacter::AGauntletCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void AGauntletCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGauntletCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Rotate the player
	if (isMovingFB && !isMovingLR)
	{
		shootDirection.Y = 0.0f;
	}
	else if (isMovingLR && !isMovingFB)
	{
		shootDirection.X = 0.0f;
	}
}

// Called to bind functionality to input
void AGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &AGauntletCharacter::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AGauntletCharacter::MoveLeftRight);
	//PlayerInputComponent->BindAxis("Shoot", this, &AGauntletCharacter::Shoot);
	PlayerInputComponent->BindAction("UsePotion", IE_Pressed, this, &AGauntletCharacter::UsePotion);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	int32 PlayerIndex = PC->GetLocalPlayer()->GetControllerId();

	switch (PlayerIndex)
	{
	case 0:
		PlayerInputComponent->BindAction("Shoot_P1", IE_Pressed, this, &AGauntletCharacter::Shoot);
		break;

	case 1:
		PlayerInputComponent->BindAction("Shoot_P2", IE_Pressed, this, &AGauntletCharacter::Shoot);
		break;

	case 2:
		PlayerInputComponent->BindAction("Shoot_P3", IE_Pressed, this, &AGauntletCharacter::Shoot);
		break;

	case 3:
		PlayerInputComponent->BindAction("Shoot_P3", IE_Pressed, this, &AGauntletCharacter::Shoot);
		break;

	default:
		break;
	}

}

void AGauntletCharacter::MoveForwardBack(float value)
{
	if (Controller && value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
		shootDirection.X = value;
		isMovingFB = true;
	}
	else
	{
		isMovingFB = false;
	}
}

void AGauntletCharacter::MoveLeftRight(float value)
{
	if (Controller && value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
		shootDirection.Y = value;
		isMovingLR = true;
	}
	else
	{
		isMovingLR = false;
	}
}

void AGauntletCharacter::Shoot()
{
	//AActor* Owner = GetOwner();
	//FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
	//FRotator SpawnRotation = GetActorRotation();
	FVector SpawnLocation = GetActorLocation() + shootDirection * 50;
	SpawnLocation.Z = GetActorLocation().Z / 2;
	FRotator SpawnRotation = shootDirection.Rotation();
	SpawnRotation.Pitch += 90.0f;

	FActorSpawnParameters SpawnParams;
	APlayerProjectile* Projectile = GetWorld()->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	//FVector Dir = GetActorForwardVector();
	FVector Dir = shootDirection;
	Projectile->Init(Dir);
}

void AGauntletCharacter::UsePotion()
{

}