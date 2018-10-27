// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Tick (called every frame)
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = (GetPawn());
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerTank && ControlledTank)) { return; }

		//Move toward player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false, DefaultNavigationFilterClass, true);

		// Aim toward player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetTargetLocation());

		// Fire if ready
		AimingComponent->Fire();
}


