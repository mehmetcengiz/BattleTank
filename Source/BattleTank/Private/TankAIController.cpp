// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay(){
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* inPawn){
	Super::SetPawn(inPawn);
	if(inPawn){
		auto possessedTank = Cast<ATank>(inPawn);
		if (!ensure(possessedTank)) { return; }

		//TODO Subscribe our local method to the tank's death event.
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath(){
	UE_LOG(LogTemp, Warning, TEXT("Received!"));

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
	
	//Fire if ready.
	if(aimingComponent->GetFiringState() == EFiringState::LOCKED)
		aimingComponent->Fire();//TODO dont fire every frame.
	

}


