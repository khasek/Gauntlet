// Fill out your copyright notice in the Description page of Project Settings.


#include "LobberRockHandler.h"

// Sets default values
ALobberRockHandler::ALobberRockHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALobberRockHandler::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ALobberRockHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deathTimer += DeltaTime;
	FVector NewLocation = GetActorLocation() + MoveDirection * speed * DeltaTime;

	FHitResult Hit;
	SetActorLocation(NewLocation, true, &Hit);

	if (Hit.bBlockingHit) {

		AActor* HitActor = Hit.GetActor();

		if (HitActor->ActorHasTag("Player")) {
			UGameplayStatics::ApplyDamage(HitActor, 10, nullptr, this, UDamageType::StaticClass());
			
			Destroy();
		}
	}

	if (deathTimer >= lifetime) {
		Destroy();
	}


}

void ALobberRockHandler::Init(const FVector& Direction)
{
	MoveDirection = Direction.GetSafeNormal();
}
