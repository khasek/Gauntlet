/* Just a simple moving cube with which to test player control basics */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestMovingCube.generated.h"

UCLASS()
class GAUNTLET_API ATestMovingCube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestMovingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* MovementComponent;

	void MoveForwardBack(float value);
	void MoveLeftRight(float value);
};
