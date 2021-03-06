// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack *leftTrack, UTankTrack *rightTrack);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMove(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurn(float Throw);
		

private:
	//Called from the pathfinding logic by the AI controllers.
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *leftTrack = nullptr;
	UTankTrack *rightTrack = nullptr;
};
