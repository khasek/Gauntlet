/*******************************************************************************
* CameraManager manages a shared top-down game camera that follows active
* players and clamps to a specified playable area.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "CameraManager.h"

/// <summary>
/// Initializes a top-down camera component
/// </summary>
ACameraManager::ACameraManager()
{
	PrimaryActorTick.bCanEverTick = true;

    // Initialize a camera component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    camera->SetupAttachment(RootComponent);

    // Make the camera look straight down
    camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

/// <summary>
/// The camera positions itself midway between any active players
/// </summary>
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
    if (playerTargets.Num() == 0)
        return;

    UpdateCameraLocation();
}

/// <summary>
/// Update location every tick, rather than managing location updates
/// from up to four players
/// </summary>
/// <param name="DeltaTime"></param>
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateCameraLocation();
}

/// <summary>
/// Add a player to the list of players the camera is following
/// </summary>
/// <param name="target">A new player to target</param>
void ACameraManager::AddPlayerTarget(AActor* target)
{
    playerTargets.Add(target);
    UpdateCameraLocation();
}

/// <summary>
/// Reset the camera's current position based on the positions of active players
/// </summary>
void ACameraManager::UpdateCameraLocation()
{
    FVector playerMidpoint = GetAveragePlayerLocation();
    FVector newLocation = ClampCameraPosition(playerMidpoint + positionOffset);

    this->SetActorLocation(newLocation);
}

/// <summary>
/// Average all player coordinates to determine a midpoint
/// </summary>
/// <returns>A midpoint between all active players</returns>
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

/// <summary>
/// Returns a position as close to the target position as possible without
/// exceeding a predefined range limit
/// </summary>
/// <param name="desiredLocation">The location the camera is trying to move to</param>
/// <returns>A clamped location</returns>
FVector ACameraManager::ClampCameraPosition(const FVector& desiredLocation) const
{
    float ClampedX = FMath::Clamp(desiredLocation.X, mapMinBounds.X, mapMaxBounds.X);
    float ClampedY = FMath::Clamp(desiredLocation.Y, mapMinBounds.Y, mapMaxBounds.Y);
    return FVector(ClampedX, ClampedY, desiredLocation.Z);
}
