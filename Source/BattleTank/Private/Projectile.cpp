// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"

#define OUT

// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);


	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	collisionMesh-> OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float speed) {
	UE_LOG(LogTemp, Warning, TEXT("LAUNCHINGG !!!"));
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();

	SetRootComponent(impactBlast);
	collisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()	//damage all actors.
	);


	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(OUT timer, this, &AProjectile::OnTimerExpire, destroyDelay, false);
}

void AProjectile::OnTimerExpire(){
	Destroy();
}