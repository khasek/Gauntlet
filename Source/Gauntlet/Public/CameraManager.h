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

	UFUNCTION(BlueprintCallable)
	void AddPlayerTarget(AActor* NewTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetAveragePlayerLocation() const;
	FVector ClampCameraPosition(const FVector& DesiredLocation) const;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
	FVector2D mapMinBounds = FVector2D(-3000.0f, -3000.0f);

	UPROPERTY(EditAnywhere)
	FVector2D mapMaxBounds = FVector2D(3000.0f, 3000.0f);

	UPROPERTY(EditAnywhere)
	FVector positionOffset = FVector(0.0f, 0.0f, 2000.0f);

	void UpdateCameraLocation();

	TArray<AActor*> playerTargets;
};
