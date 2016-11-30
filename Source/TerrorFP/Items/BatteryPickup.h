// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "BatteryPickup.generated.h"

UCLASS()
class TERRORFP_API ABatteryPickup : public AActor
{
	GENERATED_BODY()
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
    UBoxComponent* BoxCollision;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* Cube;
    
public:	
	// Sets default values for this actor's properties
	ABatteryPickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // Overlap on box collider stuff
    UPROPERTY(BlueprintAssignable, Category = "Collision" )
    FComponentBeginOverlapSignature OnComponentBeginOverlap;
    
    UPROPERTY(BlueprintAssignable, Category = "Collision" )
    FComponentEndOverlapSignature OnComponentEndOverlap;
    
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
    
    UPROPERTY(EditDefaultsOnly, Category = "Battery System")
    int32 BatteryPickupAmount = 25;
    
};
