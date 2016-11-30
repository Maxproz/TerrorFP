// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class TERRORFP_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // The static mesh of the floating actor
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMesh;
    
    // The maximum height value that the actor is going to reach.
    UPROPERTY(EditAnywhere, Category = "Timeline")
    float MaxBounceHeight;
    
    // Curve float reference
    UPROPERTY(EditAnywhere, Category = "Timeline")
    UCurveFloat* CurveFloat;
    
    
private:
    // The initial location of the actor
    FVector ActorInitialLocation;
    
    // The target location which is based on the max bounce height
    FVector TargetLocation;
    
    // The timeline that will make the actor float
    FTimeline MyTimeline;
    
    // The function that will handle every tick of the float curve
    UFUNCTION()
    void HandleProgress(float Value);
	
};
