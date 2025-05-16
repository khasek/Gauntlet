// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FireballHandling.h"
#include "LobberRockHandler.h"
#include "EightDirectionChaseComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAUNTLET_API UEightDirectionChaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEightDirectionChaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float movementSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float lobberRunDistance = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float lobberAttackDistance = 800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool lobberMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool sorcMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool demonMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float blinkInterval = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float blinkFadeDuration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float blinkDistance = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float blinkTimer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool phasingOut = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool invisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float blinkFadeTimer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fireballTimer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rockTimer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool shooting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Fireball")
	TSubclassOf<AFireballHandling> FireballClass;

	UPROPERTY(EditDefaultsOnly, Category = "Rock")
	TSubclassOf<ALobberRockHandler> RockClass;

	UFUNCTION(BlueprintCallable, Category = "EnemyAI")
	bool HasLineOfSight(AActor* Target);

	void SetOwnerOpacity(float Opacity);

	UFUNCTION(BlueprintCallable, Category = "EnemyAI")
	AActor* FindNearestPlayer();

	FVector Get8DirectionVector(FVector ToTarget);

private:
	

		
};
