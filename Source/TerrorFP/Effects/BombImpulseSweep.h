// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "BombImpulseSweep.generated.h"

UCLASS()
class TERRORFP_API ABombImpulseSweep : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombImpulseSweep();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    /*
    In this case, I will manually place some Actors near my “Bomb” Actor.
    This technique is just for demonstration purposes,
    if you wanted to simulate a bomb you should perform a sphere sweep
    and then store all the hits into the TArray seen below.*/
    
    /*Radius of the impulse*/
    UPROPERTY(EditAnywhere)
    float Radius;
    
    /*Strength of the impulse*/
    UPROPERTY(EditAnywhere)
    float Strength;
    
    /*A dynamic array of nearby actors*/
    UPROPERTY(EditAnywhere)
    TArray<AActor*> NearbyActors;


};
