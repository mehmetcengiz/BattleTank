// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());

	//Move towards the player
	MoveToActor(playerTank,acceptanceRadius);
	//Aim towards the player
	if (playerTank) {
		controlledTank->AimAt(playerTank->GetActorLocation());
		//Fire if ready
		controlledTank->Fire();//TODO dont fire every frame.
	}

}


