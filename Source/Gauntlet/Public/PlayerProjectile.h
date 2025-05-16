// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_TakeDamage.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class GAUNTLET_API APlayerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(const FVector& Direction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCombat")
	float Damage = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCombat")
	float Speed = 1000.f;

private:
	FVector MoveDirection;

};
