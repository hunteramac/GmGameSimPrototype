// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SimPawn.generated.h"

UCLASS()
class MYPROJECT4_API ASimPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASimPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// for now, we can just have the sim pawn, call a method on component to say 'I'm done' handling sim step.
	UFUNCTION(BlueprintImplementableEvent, Category = "SimManaged")
	void ExecuteSimTick(FTimespan simStep);
};
