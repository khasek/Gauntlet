// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
	FHitResult Hit;

	SetActorLocation(NewLocation, true, &Hit);

	if (Hit.bBlockingHit) {
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UBPI_TakeDamage::StaticClass())) {
			IBPI_TakeDamage::Execute_ApplyDamage(HitActor, Damage);
			//UE_LOG(LogTemp, Warning, TEXT("DamageDealt"));
		}
		Destroy();
	}
}

void APlayerProjectile::Init(const FVector& Direction)
{
	MoveDirection = Direction.GetSafeNormal();
}