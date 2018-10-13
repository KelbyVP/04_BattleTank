// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine./World.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// rotate the barrel the right amount this frame
	// given the max elevation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp(RawNewElevation, MinDegrees, MaxDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
