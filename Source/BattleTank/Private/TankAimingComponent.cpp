// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *barrelToSet){
	if (!barrelToSet) { return; }
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet){
	if (!turretToSet) { return; }
	turret = turretToSet;
}


void UTankAimingComponent::AimAt(FVector hitLocation,float launchSpeed){
	if (!barrel) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));


	//Calculate the out launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // paramater must be present to prevent bug.
	);

	if(bHaveAimSolution) {
			auto aimDirection = outLaunchVelocity.GetSafeNormal();
			auto tankName = GetOwner()->GetName();
			MoveBarrelTowards(aimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection){
	
	//Work out difference between current barrel rotation, and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
	turret->Rotate(deltaRotator.Yaw);

}
