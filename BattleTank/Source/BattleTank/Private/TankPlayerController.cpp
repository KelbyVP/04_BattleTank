// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPlayerController.h"
#include "BattleTank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>GetPawn());
};


