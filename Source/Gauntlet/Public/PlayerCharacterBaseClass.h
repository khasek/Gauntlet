// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerProjectile.h"
#include "PlayerCharacterBaseClass.generated.h"

UCLASS()
class GAUNTLET_API APlayerCharacterBaseClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacterBaseClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor characterColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float meleePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rangePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerProjectile")
	TSubclassOf<APlayerProjectile> ProjectileClass;


	// health component includes max health and defense
	// weapon component? separate ranged/melee components?
	// inventory, which I think can probably also be a component?
	// reference to a WBP_CharacterSection


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForwardBack(float value);
	void MoveLeftRight(float value);
	void Shoot();
	void UsePotion();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
