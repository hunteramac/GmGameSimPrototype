// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimManaged.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT4_API USimManaged : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimManaged();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//USimManager* manager;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// needs a callback? No, we can have it call the SimManagers public delegate for prototyping simplicity.
	//UFUNCTION(BlueprintImplementableEvent, Category = "SimManaged")
	bool ExecuteSimTick(FTimespan SimStep);
	// I can just subclass this sim managed component, specific to any sim managed I want to add it to.
	// and get parent/do casting there

	UFUNCTION(BlueprintCallable)
	void SimTickCompleted();
};
