// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel called for elevation at speed %f"), DegreesPerSecond);
	// rotate the barrel the right amount this frame
	// given the max elevation speed and frame time
}
