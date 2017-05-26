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
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *barrelToSet,UTankTurret *turretToSet);

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category ="State")	
	EFiringState FiringState = EFiringState::RELOADING;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector aimDirection);
	bool IsBarrelMoving();

	UTankBarrel *barrel = nullptr;
	UTankTurret *turret = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

	double lastFireTime = 0;

	FVector aimDirection;
};
