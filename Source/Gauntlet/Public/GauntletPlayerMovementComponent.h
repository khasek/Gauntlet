// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GauntletPlayerMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAUNTLET_API UGauntletPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
//public:
//
//protected:
//	UPROPERTY(VisibleAnywhere)
//	class UFloatingPawnMovement* MovementComponent;
//
//	void MoveForwardBack(float value);
//	void MoveLeftRight(float value);
//	void Shoot();
//	void UsePotion();
//
//private:
//	float moveSpeed = 1.0f;
};
