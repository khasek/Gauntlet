// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_TakeDamage.generated.h"

/**
 * 
 */

UINTERFACE(Blueprintable)
class GAUNTLET_API UBPI_TakeDamage : public UInterface {
	GENERATED_BODY()
};


class GAUNTLET_API IBPI_TakeDamage
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void ApplyDamage(int dmgAmnt);
};
