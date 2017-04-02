// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
	Super::BeginPlay();

	auto playerTank = GetPLayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController cant find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing : %s"), *(playerTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	//TODO Move towards the player
	//Aim towards the player
	ATank* playerTank = GetPLayerTank();
	if (playerTank) {
		GetControlledTank()->AimAt(playerTank->GetActorLocation());
	}


	//Fire if ready

}

ATank* ATankAIController::GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPLayerTank() const{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
}
