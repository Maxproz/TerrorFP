// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TerrorFPProjectile.h"
#include "Animation/AnimInstance.h"
#include "FiringComponent.h"


// Sets default values for this component's properties
UFiringComponent::UFiringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
    
}


// Called when the game starts
void UFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFiringComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	
}

void UFiringComponent::OnFire()
{
    
    FTransform Transform = GetComponentToWorld();
    GetWorld()->SpawnActor<ATerrorFPProjectile>(ProjectileClass, Transform);
    
    
    
    if (FireSound != NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, Transform.GetLocation());
    }
    
    // try and play a firing animation if specified
    if (FireAnimation != NULL)
    {
        // Get the animation object for the arms mesh
        if (AnimInstance != NULL)
        {
            AnimInstance->Montage_Play(FireAnimation, 1.f);
        }
    }

}

