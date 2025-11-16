// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManaged.h"
#include "Kismet/GameplayStatics.h"
#include "SimPawn.h"
#include "SimManager.h"

// Sets default values for this component's properties
USimManaged::USimManaged()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USimManaged::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// Find out if the player controller exists. If it does, attempt to get SimManager component.
	// If we get the component, subscribe ourselves.

	// I strongly suspect that with current impl, we will end up where this code runs before controller exists.
	// We will likely need to delay/ wait till controller exists.

	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 0 for the first local player
	if (playerController)
	{
		auto simManager = playerController->GetComponentByClass<USimManager>();
		if (simManager)
		{
			simManager->Subscribe(this);
		}
	}
}


// Called every frame
void USimManaged::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimManaged::ExecuteSimTick(FTimespan SimStep)
{
	auto ParentActor = this->GetOwner();
	
	//I'll need one for regular actors, probably. For now this is fine.
	if (auto simManagedPawn = Cast<ASimPawn>(ParentActor); simManagedPawn)
		simManagedPawn->ExecuteSimTick(SimStep);

	return false;
}

void USimManaged::SimTickCompleted()
{
	//I should be storing this once. But I'm just testing things right now.
	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 0 for the first local player
	if (playerController)
	{
		auto simManager = playerController->GetComponentByClass<USimManager>();
		if (simManager)
		{
			simManager->ExecutorFinishedSimTick(this);
		}
	}
}

