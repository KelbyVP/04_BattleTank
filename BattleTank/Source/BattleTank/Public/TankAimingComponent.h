// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{ 
	Reloading, 
	Aiming, 
	Locked 
};

// Forward Declaration
class UTankBarrel;  
class UTankTurret;
class AProjectile;

// Hold barrel properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *Barrel, UTankTurret *Turret);

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringStatus = EFiringState::Reloading;

private:
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTimje, enum ELevelTick TickTykpe, FActorComponentTickFunction *ThisTickFunction) override;
	UTankAimingComponent();
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

};
