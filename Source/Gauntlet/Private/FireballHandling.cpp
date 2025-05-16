// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballHandling.h"

// Sets default values
AFireballHandling::AFireballHandling()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireballHandling::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireballHandling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + MoveDirection * speed * DeltaTime;

	FHitResult Hit;
	SetActorLocation(NewLocation, true, &Hit);

	if (Hit.bBlockingHit) {

		AActor* HitActor = Hit.GetActor();
		
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UBPI_TakeDamage::StaticClass())) {
			IBPI_TakeDamage::Execute_ApplyDamage(HitActor, 10);
		}
		if (HitActor->ActorHasTag("Player")) {
			UGameplayStatics::ApplyDamage(HitActor, 10, nullptr, this, UDamageType::StaticClass());
		}
		

		Destroy();
	}
		

}

void AFireballHandling::Init(const FVector& Direction)
{
	MoveDirection = Direction.GetSafeNormal();
}

