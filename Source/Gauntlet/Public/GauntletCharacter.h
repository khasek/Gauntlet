/*******************************************************************************
* GauntletCharacter is the base class for the four playable characters:
* Warrior, Valkyrie, Wizard, and Elf. 
* 
* Author: Kendal Hasek, Logan Sharkey
*******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerHealthComponent.h"
#include "ScoreComponent.h"
#include "InventoryComponent.h"
#include "PlayerProjectile.h"
#include "GauntletCharacter.generated.h"

UCLASS()
class GAUNTLET_API AGauntletCharacter : public APawn
{
	GENERATED_BODY()

public:
	AGauntletCharacter();
	virtual void Tick(float DeltaTime) override;

	// Note: These need to be pointers (Unreal will crash if they aren't)
	UPlayerHealthComponent* healthComponent;
	UScoreComponent* scoreComponent;
	UInventoryComponent* inventoryComponent;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float meleeStrength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rangeStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed;

	void MoveForwardBack(float value);
	void MoveLeftRight(float value);
	FVector shootDirection = FVector::ZeroVector;
	bool isMovingFB;
	bool isMovingLR;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* MovementComponent;

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void UsePotion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerProjectile")
	TSubclassOf<APlayerProjectile> ProjectileClass;
};
