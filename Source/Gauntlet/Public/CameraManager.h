/*******************************************************************************
* CameraManager manages a shared top-down game camera that follows active
* players and clamps to a specified playable area.
* 
* Author: Kendal Hasek
*******************************************************************************/

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
	ACameraManager();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddPlayerTarget(AActor* target);

protected:
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
