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

void USimManager::ExecuteSimTick()//FTimespan simStep)
{
	//
	toExecuteSimStepsOn = managed;
	//curSimStep = simStep; // In future we probably want to support adjusting sim step rate dynamically. So we do want this to update. 

	// just execute the first one in the list
	toExecuteSimStepsOn.begin()->Get()->ExecuteSimTick(curSimStep);

	//now we wait for managed to call back in ExecutorFinishedSimTick
}

void USimManager::ExecutorFinishedSimTick(TSoftObjectPtr<USimManaged> Sender)
{
	toExecuteSimStepsOn.Remove(Sender);
	//Is this the last managed in our dataStructure? Are we done executing all?
		// then start a new simTick
	if (!toExecuteSimStepsOn.IsEmpty())
		toExecuteSimStepsOn.begin()->Get()->ExecuteSimTick(curSimStep);
	else if (executingSim)
	{
		// We have to limit the speed very slightly, to avoid triggering infinite loop detection
		// for any blueprint logic using simTick
		++limiterExecCount;
		if (limiterExecCount > LoopLimiterCount)//2147483647 - 100000)
		{
			limiterExecCount = 0;
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.SetTimer(DelayTimerHandle, this, &USimManager::ExecuteSimTick, 0.000001f, false);
			return;
		}
		ExecuteSimTick();//(curSimStep); //if not, we need to continue calling next element
	}
		
}

// Called every frame
void USimManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USimManager::Subscribe(TSoftObjectPtr<USimManaged> ToManage)
{
	// post prototyping we should be concerned about newly created simManaged subscribing during a sim step.
	managed.Add(ToManage);
	return true; // could have some error handling here if we need it
}

bool USimManager::StartSim()
{
	auto count = managed.Num();
	executingSim = true;

	curSimStep = FTimespan(DefaultSimStepRate * 10000);

	// this starts a chain of calls. post prototyping we should be concerned about the chain being interrupted somehow, detecting it, and handling it.
	ExecuteSimTick();//(MyTimespan);
	return true;
}

bool USimManager::StopSim()
{
	executingSim = false;
	return true;
}
