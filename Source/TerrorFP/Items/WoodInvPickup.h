// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "WoodInvPickup.generated.h"

UCLASS()
class TERRORFP_API AWoodInvPickup : public AActor
{
	GENERATED_BODY()
	
private:
    bool bIsEmptyID(int32 SlotID) { return SlotID == 0; }
    
    // Should spawn as not "Cannot Pickup" until our spawn delay is finished.
    bool bCanPickup = false;
    
public:	
	// Sets default values for this actor's properties
	AWoodInvPickup();

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
	
    // TODO: Should this be a UFUNCTION()? Should it be public?
    UFUNCTION()
    void RecentDropDelay();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    UStaticMeshComponent* Cube;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    UBoxComponent* BoxCollision;
    
    
};
