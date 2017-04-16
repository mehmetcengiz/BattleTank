// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state.
UENUM()
enum class EFiringState : uint8 {
	RELOADING,
	AIMING,
	LOCKED
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel *barrelToSet);

	void SetTurretReference(UTankTurret *turretToSet);

	void AimAt(FVector hitLocation,float launchSpeed);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category ="State")	
	EFiringState FiringState = EFiringState::RELOADING;

private:
	UTankBarrel *barrel = nullptr;
	UTankTurret *turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
};
