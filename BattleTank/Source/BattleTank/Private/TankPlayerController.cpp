// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"





	

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto *ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank" ) );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling: %s"), *(ControlledTank->GetName()));
	}
}

// Tick
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation(0); // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

		// TODO tell controlled tank to aim at this point
	}
}

//Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const 
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float XLocation = ViewportSizeX * CrossHairXLocation;
	float YLocation = ViewportSizeY * CrossHairYLocation;
	auto ScreenLocation = FVector2D (XLocation, YLocation);


	// de-project the crosshair position to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line-trace along the look direction and see whether there is anything there (within max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
		return true;
	}
	else return false;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector const LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
		{ 
		HitLocation = HitResult.Location;
		return true;
		}
	else return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const {
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


