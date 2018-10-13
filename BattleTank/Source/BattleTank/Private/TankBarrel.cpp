// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine./World.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:  Barrel called for elevation at speed %f"), Time, DegreesPerSecond);
	// rotate the barrel the right amount this frame
	// given the max elevation speed and frame time
}
