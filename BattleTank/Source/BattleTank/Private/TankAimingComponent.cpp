// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Engine./World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
		// figure out how far off the barrel is from where we want it to be (current barrel rotation vs AimDirection)
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)); // parameter must be present to prevent bug

	if (bHaveAimSolution)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);		
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);

	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Solution Found"), Time);

	}
}


