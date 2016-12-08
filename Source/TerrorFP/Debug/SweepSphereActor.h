// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "SweepSphereActor.generated.h"

UCLASS()
class TERRORFP_API ASweepSphereActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASweepSphereActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    
    
    /*The Height of my Sphere starting from the location of the Actor*/
    UPROPERTY(EditAnywhere, Category = "Sweep")
    float SphereHeight = 200;
    
    /*The Radius of the sphere trace*/
    UPROPERTY(EditAnywhere, Category = "Sweep")
    float SphereRadius = 500;
    
    /*Sphere segments - used for visualization only*/
    UPROPERTY(EditAnywhere, Category = "Sweep")
    int32 Segments = 100;
	
    static FORCEINLINE bool VTraceSphere(
                                         AActor* ActorToIgnore,
                                         const FVector& Start,
                                         const FVector& End,
                                         const float Radius,
                                         FHitResult& HitOut,
                                         ECollisionChannel TraceChannel=ECC_Pawn
                                         )
    {
        FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
        TraceParams.bTraceComplex = true;
        //TraceParams.bTraceAsyncScene = true;
        TraceParams.bReturnPhysicalMaterial = false;
        
        //Ignore Actors
        TraceParams.AddIgnoredActor(ActorToIgnore);
        
        //Re-initialize hit info
        HitOut = FHitResult(ForceInit);
        
        //Get World Source
        TObjectIterator<class APlayerController > ThePC;
        if(!ThePC) return false;
        
        
        return ThePC->GetWorld()->SweepSingleByChannel(
                                              HitOut,
                                              Start,
                                              End,
                                              FQuat(),
                                              TraceChannel,
                                              FCollisionShape::MakeSphere(Radius),
                                              TraceParams
                                              );
        
    }
};




