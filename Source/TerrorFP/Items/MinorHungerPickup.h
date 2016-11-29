// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "MinorHungerPickup.generated.h"

/*
 * The player should just need to make a Blueprint, assign a material and scale the box.
 */

UCLASS()
class TERRORFP_API AMinorHungerPickup : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
	AMinorHungerPickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    UStaticMeshComponent* Cube;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    UBoxComponent* BoxCollision;
	
//    /*This function is called when an Actor enters the Trigger - 4.12 version*/
//    UFUNCTION()
//    void OnTriggerEnter(AActor* OverlapedActor, AActor* OtherActor);
//    
//    /*This function is called when an Actor exits the Trigger - 4.12 version*/
//    UFUNCTION()
//    void OnTriggerExit(AActor* OverlapedActor, AActor* OtherActor);
    
    
    // Overlap on box collider stuff
    UPROPERTY(BlueprintAssignable, Category = "Collision" )
    FComponentBeginOverlapSignature OnComponentBeginOverlap;
    
    UPROPERTY(BlueprintAssignable, Category = "Collision" )
    FComponentEndOverlapSignature OnComponentEndOverlap;
    
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    
};
