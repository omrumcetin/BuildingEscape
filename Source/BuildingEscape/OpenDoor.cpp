// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ActorThatOpens) return;
	Owner = GetOwner();
	if (!Owner) return;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetTotalMassOfActorsOnPlate()>30)
	{
		OnOpen.Broadcast();
	}
	else 
	{
		OnClose.Broadcast();
	}
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) return 0.0;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* OverlappedActor : OverlappingActors)
	{
		TotalMass += OverlappedActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on pressure plate. Mass is : %f"), *(OverlappedActor->GetName()), TotalMass);
	}
	

	return TotalMass;
}
