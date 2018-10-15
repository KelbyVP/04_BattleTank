// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "AIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("DONKEY:  C++ Begin Play called for Tank AI Controller"))

}



// Tick (called every frame)
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false, DefaultNavigationFilterClass, true);

		// Aim toward player
		ControlledTank->AimAt(PlayerTank->GetTargetLocation());

		// Fire if ready
		ControlledTank->Fire();  // TODO don't fire every frame
	}
}


