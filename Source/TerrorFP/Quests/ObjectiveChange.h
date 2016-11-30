// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectiveChange.generated.h"

UCLASS()
class TERRORFP_API AObjectiveChange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveChange();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    /*This function is called when an Actor enters the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor);
    
    /*This function is called when an Actor exits the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerExit(AActor* OverlappedActor, AActor* OtherActor);
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* BoxCollider;
    
    UPROPERTY(EditAnywhere, Category = "Quest System")
    FString NextQuest;
    
};
