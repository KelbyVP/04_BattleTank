// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegrees = 40;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinDegrees = 0;


public:
	// -1 is max downward movement, and +1 is max up movement
	void Elevate(float RelativeSpeed);
	
	
	
};
