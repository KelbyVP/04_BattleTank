// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine./World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}
void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
		// figure out how far off the barrel is from where we want it to be (current barrel rotation vs AimDirection)
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
}
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }
	// figure out how far off the barrel is from where we want it to be (current barrel rotation vs AimDirection)
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }
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
		MoveTurretTowards(AimDirection);
	}
}


