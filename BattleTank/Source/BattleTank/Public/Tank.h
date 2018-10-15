// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine./World.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declarations
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY (BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();
	UTankBarrel * Barrel;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;




	
};
