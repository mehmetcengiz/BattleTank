// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();
	auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(aimingComponent)){
		FoundAimingComponent(aimingComponent);
	}else{
		UE_LOG(LogTemp,Warning,TEXT("Player controller can't find aiming component at Begin Play"))
	}

}

void ATankPlayerController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController:: GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!ensure(GetControlledTank())) { return; }

	FVector hitLocation ;//OUT parameter.

	if(GetSightRayHitLocation(OUT hitLocation)) {
		GetControlledTank()->AimAt(hitLocation);
	}




	//If it hits the landscape
		//Tell controlled tank to aim at this point.
}

	//Get world location if linetrace through crosshair.
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const{
	

	//Find the crosshair position.
	int32 viewportSizeX,viewportSizeY;
	GetViewportSize(OUT viewportSizeX,OUT viewportSizeY);
	auto screenLocation = FVector2D(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);

	//"De-project" the screen position of the crosshair to a world direction.
	FVector lookDirection;
	if(GetLookDirection(screenLocation, OUT lookDirection)) {
		//Line-trace along that lookDirection, and see what we hit(up to max range.)
		GetLookVectorHitLocation(lookDirection, OUT hitLocation);

	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection,FVector& hitLocation) const{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			OUT hitResult,
			startLocation,
			endLocation,
			ECC_Visibility)) {
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;	//Line trace didn't succed.
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const {

	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}