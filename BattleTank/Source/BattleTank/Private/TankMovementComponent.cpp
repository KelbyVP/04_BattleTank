// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{

	//auto Time = GetWorld->GetTimeSeconds();
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s intends move forward at throw = %f"), *Name, Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO preventg double-speed due to control using both stick and shoulder buttons
	
}


