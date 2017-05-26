// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	//How close the AI tank get.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float acceptanceRadius = 80000;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	


};
