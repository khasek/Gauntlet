// Fill out your copyright notice in the Description page of Project Settings.


#include "EightDirectionChaseComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UEightDirectionChaseComponent::UEightDirectionChaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	// ...
}


// Called when the game starts
void UEightDirectionChaseComponent::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}

//So the sorcerers don't teleport inside the player
float StopDistance = 100.0f;

// Called every frame
void UEightDirectionChaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//UE_LOG(LogTemp, Log, TEXT("TickComponent is running"));

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Target = FindNearestPlayer();

	AActor* Owner = GetOwner();
	if (!Owner) return;

	//Handles movement for the lobber, who runs away if the player is too close0
	if (lobberMovement) {
		rockTimer += DeltaTime;
		if (Target) {
			FVector awayVector = Owner->GetActorLocation() - Target->GetActorLocation();
			awayVector.Z = 0;

			float distance = awayVector.Size();

			if (distance <= lobberAttackDistance) {
				printf("Player in range");
				if (rockTimer >= 3.0f) {
					rockTimer = 0.0f;
					FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100;
					FRotator SpawnRotation = (Target->GetActorLocation() - Owner->GetActorLocation()).Rotation();

					FActorSpawnParameters SpawnParams;
					ALobberRockHandler* Rock = GetWorld()->SpawnActor<ALobberRockHandler>(RockClass, SpawnLocation, SpawnRotation, SpawnParams);
					if (Rock) {
						FVector Direction = Target->GetActorLocation() - SpawnLocation;
						Rock->Init(Direction);
					}
					if (!Rock) {
						UE_LOG(LogTemp, Error, TEXT("Failed to spawn Lobber rock!"));
					}
				}

				if (distance < lobberRunDistance) {
					FVector Dir = Get8DirectionVector(awayVector);
					FVector NewLocation = Owner->GetActorLocation() + Dir * movementSpeed * DeltaTime;

					FHitResult hit;

					Owner->SetActorLocation(NewLocation, true, &hit);

					if (!awayVector.IsNearlyZero()) {
						FRotator LookAtRotation = (-awayVector).Rotation();
						Owner->SetActorRotation(LookAtRotation);
					}
				}
			}

			return;
		}

		//Scuffed Sorcerer code, the opacity doesn't changing doesn't work but it was attempted
		if (sorcMovement) {
			//UE_LOG(LogTemp, Warning, TEXT("sorcMovement Reached"));
			blinkTimer += DeltaTime;

			if (blinkTimer >= blinkInterval && !phasingOut) {
				phasingOut = true;
				blinkFadeTimer = 0.0f;
				//UE_LOG(LogTemp, Warning, TEXT("Phasing set to true"));
			}

			if (phasingOut && HasLineOfSight(Target)) {
				blinkFadeTimer += DeltaTime;

				float Opacity = FMath::Lerp(1.0f, 0.0f, blinkFadeTimer / blinkFadeDuration);

				//SetOwnerOpacity(Opacity);
				//UE_LOG(LogTemp, Warning, TEXT("Opacity setting reached"));
				if (blinkFadeTimer >= blinkFadeDuration && !invisible) {
					Target = FindNearestPlayer();
					if (Target && HasLineOfSight(Target)) {
						FVector Dir = (Target->GetActorLocation() - Owner->GetActorLocation());
						float dist = Dir.Size();
						Dir = Dir.GetSafeNormal2D();
						if (dist < blinkDistance) {
							blinkDistance = dist - 100;

						}
						if (blinkDistance < 100)
							blinkDistance = 0;


						FVector blinkLocation = Owner->GetActorLocation() + Dir * blinkDistance;

						Owner->SetActorLocation(blinkLocation, true);
					}
					//UE_LOG(LogTemp, Warning, TEXT("Opacity: %f"), Opacity);
					invisible = true;
					blinkFadeTimer = 0.0f;
				}
				else if (invisible && blinkFadeTimer >= blinkFadeDuration) {

					phasingOut = false;
					invisible = false;
					blinkTimer = 0.0f;

				}
				else if (invisible) {
					blinkFadeTimer += DeltaTime;
					Opacity = FMath::Lerp(0.0f, 1.0f, blinkFadeTimer / blinkFadeDuration);
					//SetOwnerOpacity(Opacity);
				}
			}
			blinkDistance = 600.0f;
			return;
		}

		//Handles movement and shooting for demons, who stop to shoot when they have LOS
		if (demonMovement) {
			fireballTimer += DeltaTime;
			if (HasLineOfSight(Target)) {
				shooting = true;
				if (fireballTimer >= 3.0f) {
					fireballTimer = 0.0f;
					FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100;
					FRotator SpawnRotation = (Target->GetActorLocation() - Owner->GetActorLocation()).Rotation();

					FActorSpawnParameters SpawnParams;
					AFireballHandling* Fireball = GetWorld()->SpawnActor<AFireballHandling>(FireballClass, SpawnLocation, SpawnRotation, SpawnParams);
					if (Fireball) {
						FVector Direction = Target->GetActorLocation() - SpawnLocation;
						Fireball->Init(Direction);
					}
				}
			}
			else
				shooting = false;
		}

		//Base movement script, tries to move towards player at all times
		if (Target && !shooting) {
			FVector ToTarget = Target->GetActorLocation() - Owner->GetActorLocation();
			ToTarget.Z = 0.0f; // ensure 2D movement only

			float Distance = ToTarget.Size();

			if (Distance > StopDistance)
			{
				FVector Dir = Get8DirectionVector(ToTarget);
				FVector NewLocation = Owner->GetActorLocation() + Dir * movementSpeed * DeltaTime;
				FHitResult Hit;
				Owner->SetActorLocation(NewLocation, true, &Hit);

				if (Hit.bBlockingHit)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *Hit.GetActor()->GetName());
					//if (Hit.GetActor()->GetClass()->ImplementsInterface(UBPI_TakeDamage::StaticClass()))
					//{
					//	// Trigger melee logic here
					//	UE_LOG(LogTemp, Warning, TEXT("Hit the player!"));
					//}
				}


				//Owner->SetActorLocation(NewLocation, true, &Hit);
				//Owner->SetActorLocation(NewLocation);
			}

			if (!ToTarget.IsNearlyZero())
			{
				FRotator LookAtRotation = ToTarget.Rotation();
				Owner->SetActorRotation(LookAtRotation);
			}
		}
	}
}

AActor* UEightDirectionChaseComponent::FindNearestPlayer() {
	AActor* Nearest = nullptr;
	float ClosestDistSq = FLT_MAX;

	//Finds all posessed pawns and checks their distance to owner
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		APawn* PlayerPawn = It->Get()->GetPawn();
		if (PlayerPawn) {
			float DistSq = FVector::DistSquared(PlayerPawn->GetActorLocation(), GetOwner()->GetActorLocation());
			if (DistSq < ClosestDistSq) {
				ClosestDistSq = DistSq;
				Nearest = PlayerPawn;
			}
		}
	}
	return Nearest;
}

FVector UEightDirectionChaseComponent::Get8DirectionVector(FVector ToTarget) {
	ToTarget.Z = 0.0f;

	if (ToTarget.IsNearlyZero())
		return FVector::ZeroVector;

	ToTarget.Normalize();

	// Get angle to target player in degrees between 0 and 360
	float Angle = FMath::RadiansToDegrees(FMath::Atan2(ToTarget.Y, ToTarget.X));
	if (Angle < 0.0f)
		Angle += 360.0f;

	// Determine which of the 8 directions to use, angle math is weird
	int32 Sector = FMath::FloorToInt((Angle + 22.5f) / 45.0f) % 8;

	//UE_LOG(LogTemp, Warning, TEXT("Angle: %f, Sector: %d"), Angle, Sector); log used to help bug solve

	FVector Directions[8] = {
		FVector(1, 0, 0),                                // 0°   - East
		FVector(1, 1, 0),                                // 45°  - NE
		FVector(0, 1, 0),                                // 90°  - North
		FVector(-1, 1, 0),                               // 135° - NW
		FVector(-1, 0, 0),                               // 180° - West
		FVector(-1, -1, 0),                              // 225° - SW
		FVector(0, -1, 0),                               // 270° - South
		FVector(1, -1, 0)                                // 315° - SE
	};

	//UE_LOG(LogTemp, Warning, TEXT("Sector: %d, Direction: %s"), Sector, *Directions[Sector].ToString()); log used to help bug solve
	


	FVector Chosen = Directions[Sector].GetSafeNormal();

	return Chosen;
}

void UEightDirectionChaseComponent::SetOwnerOpacity(float Opacity) {
	AActor* Owner = GetOwner();
	if (!Owner) return;

	TArray<UMeshComponent*>(Meshes);
	Owner->GetComponents<UMeshComponent>(Meshes);

	for (UMeshComponent* Mesh : Meshes) {
		int32 NumMats = Mesh->GetNumMaterials();
		for (int32 i = 0; i < NumMats; ++i) {
			UMaterialInstanceDynamic* dynamicMat = Mesh->CreateAndSetMaterialInstanceDynamic(i);
			if (dynamicMat)
				dynamicMat->SetScalarParameterValue("Opacity", Opacity);
		}
	}
}

bool UEightDirectionChaseComponent::HasLineOfSight(AActor* Target) {
	FHitResult hitResult;
	AActor* Owner = GetOwner();
	//UE_LOG(LogTemp, Warning, TEXT("HasLineOfSight Reached"));

	FVector Start = Owner->GetActorLocation();
	FVector End = Target->GetActorLocation();

	FCollisionQueryParams TraceParams(FName(TEXT("LineOfSightTrace")), true, Owner);
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(Owner);

	TArray<FHitResult> HitResults;

	//Tries to raycast through enemies so that they can shoot the player still
	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, TraceParams);

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();

		if (!IsValid(HitActor))
			continue;

		if (HitActor == Target)
			return true;

		if (!HitActor->ActorHasTag("Enemy"))
			return false;

	}
	
	return false; 


	/*bool hit = GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility, TraceParams);

	AActor* HitActor = hitResult.GetActor();
	
	if (HitActor == Target) {
		return true;
	}
	
	return false;*/

}




