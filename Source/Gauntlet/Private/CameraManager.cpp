// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    camera->SetupAttachment(RootComponent);

    // Make the camera look straight down
    camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
    if (playerTargets.Num() == 0)
        return;

    FVector midpoint = GetAveragePlayerLocation();
    FVector desiredLocation = FVector(midpoint.X, midpoint.Y, positionOffset.Z);
    SetActorLocation(ClampCameraPosition(desiredLocation));
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // I think it's more efficient to have the camera handle its own positioning
    // update every frame, rather than make players notify it every time they
    // move, which could potentially make the camera update itself four
    // times per frame.
    UpdateCameraLocation();
}

void ACameraManager::SetPlayerTargets(const TArray<AActor*>& NewTargets)
{
    playerTargets = NewTargets;
    UpdateCameraLocation();
}

void ACameraManager::UpdateCameraLocation()
{
    /*FVector zOffset = FVector(0, 0, cameraHeight);*/
    FVector playerMidpoint = GetAveragePlayerLocation();
    FVector newLocation = ClampCameraPosition(playerMidpoint + positionOffset);

    this->SetActorLocation(newLocation);
}

FVector ACameraManager::GetAveragePlayerLocation() const
{
    FVector sum = FVector::ZeroVector;
    for (AActor* target : playerTargets)
    {
        if (target)
        {
            sum += target->GetActorLocation();
        }
    }
    return sum / playerTargets.Num();
}

FVector ACameraManager::ClampCameraPosition(const FVector& desiredLocation) const
{
    float ClampedX = FMath::Clamp(desiredLocation.X, mapMinBounds.X, mapMaxBounds.X);
    float ClampedY = FMath::Clamp(desiredLocation.Y, mapMinBounds.Y, mapMaxBounds.Y);
    return FVector(ClampedX, ClampedY, desiredLocation.Z);
}
