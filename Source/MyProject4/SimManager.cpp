// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

// Sets default values for this component's properties
USimManager::USimManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USimManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void USimManager::executeSimTick(FTimespan simStep)
{
	// setup some way to know that all sim managed complete their execution in the next step.
	// we may want to stagger handling in some case (combat), rather then having it all run asyncronously

	for (auto specific: managed)
	{
		// Call sim managed 'execute sim step with time step.
		specific->ExecuteSimTick(simStep);
		// wait for it to finish before continuing onto the next sim managed?
	}

	// wait for callbacks

	// on getting callbacks, execute next sim tick (unless sim has been commanded to stop)
}


// Called every frame
void USimManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimManager::Subscribe(TSoftObjectPtr<USimMananged> toManage)
{
	managed.Add(toManage);
	return true; // could have some error handling here if we need it
}

bool USimManager::StartSim()
{
	auto count = managed.Num();
	executingSim = true;
	FTimespan MyTimespan(0, 0, 0, 1);
	
	// this is almost certainly a bad way to define repeat exec. probably will be 
	// caught by infinite loop detection.
	// This should actually be an event/async.
	//while(executingSim)

	//just do once cylce for now.
	executeSimTick(MyTimespan);
	return true;
}

bool USimManager::StopSim()
{
	executingSim = false;
	return true;
}

void USimManager::executorFinishedSimTick(TSoftObjectPtr<USimMananged> sender)
{
	// we'll need to keep track of these, maintaining some outgoing commands 'set' and removing them as 
	// responses like this one come in matching the reference.
	// Once it's empty, we should trigger another sim step.
}
