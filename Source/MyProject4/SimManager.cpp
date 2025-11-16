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

	//this should actually be handled in ExecutorFinishedSimTick

	// just execute the first one in the list
	auto specific = managed.begin()->Get();
	specific->ExecuteSimTick(simStep);

	//now we wait for managed to call back in ExecutorFinishedSimTick

	// 
	//for (auto specific: managed)
	//{
	//	// Call sim managed 'execute sim step with time step.
	//	specific->ExecuteSimTick(simStep);
	//	// wait for it to finish before continuing onto the next sim managed?
	//}

	// wait for callbacks

	// on getting callbacks, execute next sim tick (unless sim has been commanded to stop)
}

void USimManager::ExecutorFinishedSimTick(TSoftObjectPtr<USimManaged> Sender)
{
	//Is this the last managed in our dataStructure? Are we done executing all?
		// then start a new simTick

	// if not, we need to continue calling next element
}



// Called every frame
void USimManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimManager::Subscribe(TSoftObjectPtr<USimManaged> ToManage)
{
	// post prototyping we should be concerned about newly created simMananged subscribing during a sim step.
	managed.Add(ToManage);
	return true; // could have some error handling here if we need it
}

bool USimManager::StartSim()
{
	auto count = managed.Num();
	executingSim = true;
	FTimespan MyTimespan(0, 0, 0, 1);

	// this starts a chain of calls. post prototyping we should be concerened about the chain being interrupted somehow, detecting it, and handling it.
	executeSimTick(MyTimespan);
	return true;
}

bool USimManager::StopSim()
{
	executingSim = false;
	return true;
}
