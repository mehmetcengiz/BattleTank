// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *aimingCompRef);

	UFUNCTION()
	void OnPossedTankDeath();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* inPawn) override;

	//Start the tank moving the barrel so that a shot would it where 
	//The crosshair intersects the world.
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float crossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float crossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;



	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
