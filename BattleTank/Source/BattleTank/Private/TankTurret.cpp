// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine./World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
