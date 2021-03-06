// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

public:
	//Called by the engine when actor got damage.
	virtual float TakeDamage(float damageAmount, struct FDamageEvent const &damageEvent,
		class AController * eventInstigator, AActor *damageCauser);

	//Return current health as a percentage of starting health. 0 to 1.
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:

	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 startingHealt = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 currentHealth; // Initialised in begin play.


};
