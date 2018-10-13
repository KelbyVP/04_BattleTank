// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine./World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:  Turrer called for rotate at speed %f"), Time, RelativeSpeed);

	// rotate the turret the right amount this frame
	// given the max rotation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewYaw = RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}
