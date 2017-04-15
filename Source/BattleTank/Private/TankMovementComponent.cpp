// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack *leftTrackToSet,UTankTrack *rightTrackToSet){	
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed){
	auto tankName = GetOwner()->GetName();
	auto moveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"),*tankName,*moveVelocityString);
}

void UTankMovementComponent::IntendMove(float Throw){
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
	//TODO prevent double-speed 
}

//+1 scale for Right, -1 scale for Left
void UTankMovementComponent::IntendTurn(float Throw) {
	if (!leftTrack || !rightTrack) { return; }
	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);
}

