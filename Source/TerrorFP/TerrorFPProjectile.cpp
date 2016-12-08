// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TerrorFP.h"
#include "TerrorFPProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// TODO: Figure out how to fix the crash on overlap on my other quest objects.

ATerrorFPProjectile::ATerrorFPProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATerrorFPProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

//    RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
//    RadialForceComp->ImpulseStrength = 28084;
//    RadialForceComp->DestructibleDamage = 1.f;
    
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
    
//    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
//    StaticMeshComp->SetupAttachment(CollisionComp);
//    
//    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATerrorFPProjectile::OnOverlapBegin);
//    CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATerrorFPProjectile::OnOverlapEnd);
    
    
}

void ATerrorFPProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

//void ATerrorFPProjectile::OnOverlapBegin(class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
//{
//    
//}
//
//void ATerrorFPProjectile::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//    
//}

