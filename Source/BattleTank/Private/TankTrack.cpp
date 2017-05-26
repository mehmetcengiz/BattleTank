// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack(){
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay(){
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse,const FHitResult& Hit){
	
	DriveTrack();
	//Apply sideways force.
	ApplySidewaysForce();
	//reset throttle.
	currentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce(){
	// Calculate the slippage speed;
	auto rightVector = GetRightVector();
	auto slippageSpeed = FVector::DotProduct(rightVector, GetComponentVelocity());
	
	// Workout the required acceleration this frame to correct.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / DeltaTime * rightVector;
	
	// Calculate and apply sideways for (F = m a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2 ; // Two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::DriveTrack(){
	//TODO clamp actual throttle value so player can't over-drive.
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner() -> GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied,forceLocation);
}

void UTankTrack::SetThrottle(float throttle){
	currentThrottle =FMath::Clamp<float>(currentThrottle + throttle,-1,1);
	
}

