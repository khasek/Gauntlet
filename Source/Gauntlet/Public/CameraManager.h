// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "CameraManager.generated.h"

UCLASS()
class GAUNTLET_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlayerTargets(const TArray<AActor*>& NewTargets);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetAveragePlayerLocation() const;
	FVector ClampCameraPosition(const FVector& DesiredLocation) const;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector2D MapMinBounds = FVector2D(0.f, 0.f);

	UPROPERTY(EditAnywhere)
	FVector2D MapMaxBounds = FVector2D(5000.f, 5000.f);

	UPROPERTY(EditAnywhere)
	float CameraHeight = 1000.f;

	TArray<AActor*> PlayerTargets;
};
