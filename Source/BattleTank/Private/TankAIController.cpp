// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();
	

	if (!ensure(playerTank && controlledTank)) { return; }

	//Move towards the player
	MoveToActor(playerTank,acceptanceRadius);
	//Aim towards the player
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());
	//Fire if ready
	//TODO fix firing.
	//controlledTank->Fire();//TODO dont fire every frame.
	

}


