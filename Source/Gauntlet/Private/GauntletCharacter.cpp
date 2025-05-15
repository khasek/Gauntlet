/*******************************************************************************
* GauntletCharacter is the base class for the four playable characters:
* Warrior, Valkyrie, Wizard, and Elf.
*
* Author: Kendal Hasek, Logan Sharkey
*******************************************************************************/

#include "GauntletCharacter.h"

AGauntletCharacter::AGauntletCharacter()
{
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
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
	}
}

void AGauntletCharacter::MoveLeftRight(float value)
{
	if (Controller && value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AGauntletCharacter::Shoot()
{
	//AActor* Owner = GetOwner();
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
	FRotator SpawnRotation = GetActorRotation();
	SpawnRotation.Pitch += 90.0f;

	FActorSpawnParameters SpawnParams;
	APlayerProjectile* Projectile = GetWorld()->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	FVector Dir = GetActorForwardVector();
	Projectile->Init(Dir);
}

void AGauntletCharacter::UsePotion()
{

}