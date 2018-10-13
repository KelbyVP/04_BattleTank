// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine./World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
		// figure out how far off the barrel is from where we want it to be (current barrel rotation vs AimDirection)
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		UE_LOG(LogTemp, Warning, TEXT("Aim Rotation:  %s; Barrel Rotation: %s"), *AimAsRotator.ToString(), *BarrelRotator.ToString());
		auto DeltaRotation = AimAsRotator - BarrelRotator;

		// rotate the barrel the right amount this frame
		// given the max elevation speed and frame time
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the TossVelocity
	bool bHaveAimSolution = (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT TossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace));

	if (bHaveAimSolution)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		return;

	}
}


