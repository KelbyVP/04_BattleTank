// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveFoward(float Throw)
{

	//auto Time = GetWorld->GetTimeSeconds();
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s intends move forward at throw = %f"), *Name, Throw);
}

