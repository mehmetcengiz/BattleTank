// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
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
	barrel = barrelToSet;
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

	auto time = GetWorld()->GetTimeSeconds();//TODO It is for loging delete later.

	if(bHaveAimSolution) {
			auto aimDirection = outLaunchVelocity.GetSafeNormal();
			auto tankName = GetOwner()->GetName();
			MoveBarrelTowards(aimDirection);
			UE_LOG(LogTemp, Warning, TEXT("Barel-elevate() at %f"), time);//TODO Log to delete.
	}else{

		UE_LOG(LogTemp, Warning, TEXT("No solution is found at %f"), time);//TODO Log to delete.
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection){
	
	//Work out difference between current barrel rotation, and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	
	barrel->Elevate(5);

}
