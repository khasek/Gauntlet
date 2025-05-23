// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPI_TakeDamage.h"
#include "Kismet/GameplayStatics.h"
#include "FireballHandling.generated.h"

UCLASS()
class GAUNTLET_API AFireballHandling : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireballHandling();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(const FVector& Direction);

private:
	FVector MoveDirection;
	float speed = 600.0f;

};
