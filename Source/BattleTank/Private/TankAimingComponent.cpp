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

void UTankAimingComponent::TickComponent(float DeltaTime, enum ElevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	UE_LOG(LogTemp, Warning, TEXT("Aiming comp ticking."));
	if((FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds){
		FiringState = EFiringState::RELOADING;
	}
	//TODO Handle aiming and locked states.
}

void UTankAimingComponent::Initialise(UTankBarrel *barrelToSet, UTankTurret *turretToSet) {
	if (!ensure(barrelToSet && turretToSet)) { return; }
	barrel = barrelToSet;
	turret = turretToSet;
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
			auto aimDirection = outLaunchVelocity.GetSafeNormal();
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
	turret->Rotate(deltaRotator.Yaw);

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
