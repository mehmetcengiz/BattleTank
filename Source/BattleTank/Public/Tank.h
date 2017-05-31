// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

public:
	//Called by the engine when actor got damage.
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const &damageEvent,
		class AController * eventInstigator, AActor *damageCauser);

	// Sets default values for this pawn's properties
	ATank();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 startingHealt = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 currentHealth = startingHealt;


};
