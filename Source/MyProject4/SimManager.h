// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimManaged.h"
#include "SimManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT4_API USimManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TSet<TSoftObjectPtr<USimManaged>> managed;

	void executeSimTick(FTimespan simStep);

	bool executingSim;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Subscribe(TSoftObjectPtr<USimManaged> ToManage);

	UFUNCTION(BlueprintCallable, Category = "SimManager")
	bool StartSim();

	UFUNCTION(BlueprintCallable, Category = "SimManager")
	bool StopSim();

	void ExecutorFinishedSimTick(TSoftObjectPtr<USimManaged> Sender);
};
