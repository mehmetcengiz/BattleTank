// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay(){
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel *barrelToSet, UTankTurret *turretToSet) {
	if (!ensure(barrelToSet && turretToSet)) { return; }
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	if((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds){
		FiringState = EFiringState::RELOADING;
	}else if(IsBarrelMoving()){
		FiringState = EFiringState::AIMING;
	}else{
		FiringState = EFiringState::LOCKED;
	}
	//TODO Handle aiming and locked states.
}

bool UTankAimingComponent::IsBarrelMoving(){
	if (!ensure(barrel)) { return false; }
	auto barrelForward = barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection,0.01);
}

void UTankAimingComponent::AimAt(FVector hitLocation){
	if (!ensure(barrel)) { return; }

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
			aimDirection = outLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection){
	
	if (!ensure(barrel && turret)) { return; }

	//Work out difference between current barrel rotation, and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);
	
	//Always yaw the shortest way.
	if(deltaRotator.Yaw < 180){
		turret->Rotate(deltaRotator.Yaw);
	}else{
		turret->Rotate(-deltaRotator.Yaw);
	}
	

}

void UTankAimingComponent::Fire() {

	
	
	if (FiringState != EFiringState::RELOADING) {
		if (!ensure(barrel)) { return; }
		if (!ensure(ProjectileBluePrint)) { return; }
		//Spawn projectile.
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			barrel->GetSocketLocation(FName("Projectile")),
			barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();

	}
}

EFiringState UTankAimingComponent::GetFiringState() const{
	return FiringState;
}
