// Copyright KVP

#include "SprungWheel.h"
#include "TankTrack.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"



// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(TankAxleConstraint);

	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetupAttachment(TankAxleConstraint);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel1 = CreateDefaultSubobject<USphereComponent>(FName("Wheel1"));
	Wheel1->SetupAttachment(AxleWheelConstraint);

	Wheel2 = CreateDefaultSubobject<USphereComponent>(FName("Wheel2"));
	Wheel2->SetupAttachment(AxleWheelConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	TankAxleConstraint->SetConstrainedComponents(
		BodyRoot,
		NAME_None,
		Wheel1,
		NAME_None
	);
}
// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

