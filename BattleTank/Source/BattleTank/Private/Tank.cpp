// Copyright KelbyVP

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is dead!"))
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	//returns current health as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	return (float)CurrentHealth/(float)StartingHealth;

}
