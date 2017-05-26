// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) {return;}

	FoundAimingComponent(aimingComponent);
	

}

void ATankPlayerController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetPawn()) { return; } // e.g. if not possessing.
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation ;//OUT parameter.

	bool bGetSightRayHitLocation = GetSightRayHitLocation(hitLocation);
	if(GetSightRayHitLocation(OUT hitLocation)) {
		aimingComponent->AimAt(hitLocation);
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
		return GetLookVectorHitLocation(lookDirection, OUT hitLocation);

	}
	return false;
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