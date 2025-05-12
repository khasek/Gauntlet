// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    Camera->SetupAttachment(RootComponent);

    // Make the camera look straight down
    Camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
    if (PlayerTargets.Num() == 0)
        return;

    FVector Midpoint = GetAveragePlayerLocation();
    FVector DesiredLocation = FVector(Midpoint.X, Midpoint.Y, CameraHeight);
    SetActorLocation(ClampCameraPosition(DesiredLocation));
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraManager::SetPlayerTargets(const TArray<AActor*>& NewTargets)
{
    PlayerTargets = NewTargets;
}

FVector ACameraManager::GetAveragePlayerLocation() const
{
    FVector Sum = FVector::ZeroVector;
    for (AActor* Target : PlayerTargets)
    {
        if (Target)
        {
            Sum += Target->GetActorLocation();
        }
    }
    return Sum / PlayerTargets.Num();
}

FVector ACameraManager::ClampCameraPosition(const FVector& DesiredLocation) const
{
    float ClampedX = FMath::Clamp(DesiredLocation.X, MapMinBounds.X, MapMaxBounds.X);
    float ClampedY = FMath::Clamp(DesiredLocation.Y, MapMinBounds.Y, MapMaxBounds.Y);
    return FVector(ClampedX, ClampedY, DesiredLocation.Z);
}
