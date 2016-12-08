// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "DrawDebugHelpers.h"
#include "SweepSphereActor.h"


// Sets default values
ASweepSphereActor::ASweepSphereActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASweepSphereActor::BeginPlay()
{
	Super::BeginPlay();
	
    
    /*TArray is the collection that contains all the HitResults*/
    TArray<FHitResult> HitResults;
    
    /*The Start location of the sphere*/
    FVector StartLocation = GetActorLocation();
    
    /*The End location of the sphere is equal to the default location of the actor plus 
     the height we will enter from the editor To extend this functionality, you can 
     replace the height variable with a FVector*/
    FVector EndLocation = GetActorLocation();
    EndLocation.Z += SphereHeight;
    
    /*Search for static objects only*/
    ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
    
    /*Declare the Collision Shape, assign a Sphere shape and set it's radius*/
    FCollisionShape CollisionShape;
    CollisionShape.ShapeType = ECollisionShape::Sphere;
    CollisionShape.SetSphere(SphereRadius);
    
    /*Perform the actual raycast. This method returns true if there is at least 1 hit.*/
    bool bHitSomething = GetWorld()->SweepMultiByChannel(
    HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);
    
    // TODO: How can I get this to print the names of the objects on screen?
    // TODO: Perhaps its beacuse I need this print message OnTick?
    /*If the raycast hit a number of objects, iterate through them and print their name in the console*/
    if (bHitSomething)
    {
        for (auto It = HitResults.CreateIterator(); It; It++)
        {
            GLog->Log((*It).Actor->GetName());
        }
    }
    
    /*In order to draw the sphere of the first image, 
     I will use the DrawDebugSphere function which resides 
     in the DrawDebugHelpers.h This function needs the center
     of the sphere which in this case is provided by the following equation*/
    FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;
    
    /*Draw the sphere in the viewport*/
    DrawDebugSphere(GetWorld(),
                    CenterOfSphere,
                    CollisionShape.GetSphereRadius(),
                    Segments,
                    FColor::Green,
                    true);
    
    
    
}

// Called every frame
void ASweepSphereActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

