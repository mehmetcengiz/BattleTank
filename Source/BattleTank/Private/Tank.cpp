// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank(){
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();

	tankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector hitLocation){
	if (!tankAimingComponent) { return; }

	tankAimingComponent->AimAt(hitLocation,launchSpeed);

}

void ATank::Fire(){

	if (!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (isReloaded) {

		//Spawn projectile.
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();

	}
}
