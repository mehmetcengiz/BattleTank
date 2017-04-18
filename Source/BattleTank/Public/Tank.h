// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above


//Forward declarations.
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 4000;	//TODO find Sensible starting value 

	UPROPERTY(EditDefaultsOnly, Category= "Firing")
	float reloadTimeInSeconds = 3;
	
	double lastFireTime = 0;
	
	//Local barrel reference for spawning projectile.
	UTankBarrel *Barrel = nullptr; //TODO remove.

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

};
