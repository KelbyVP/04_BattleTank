// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine./World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickTykpe, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringState::Aiming;
	}
	else
	{
		FiringStatus = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelVector = Barrel->GetForwardVector();
	return !(BarrelVector.Equals(AimDirection, .01));
}


void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
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
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - TurretRotator;
	if (FMath::Abs(DeltaRotator.Yaw) > 180) {
		DeltaRotator.Yaw = -(360-DeltaRotator.Yaw);
	}
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//if (!ensure(Barrel)) { return; }
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
		AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);		
		MoveTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{


	if (FiringStatus != EFiringState::Reloading) {
		if (!ensure(Barrel)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}



