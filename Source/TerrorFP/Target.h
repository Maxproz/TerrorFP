// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class TERRORFP_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    /**This is the static mesh for the component*/
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* TargetMesh;
    
    /**This is the function that is called when the targets health falls below 0*/
	void DestroyTarget();
    
    /**This is a value from 0-100 and, and represents the health of the target*/
    float Health;
    
    /** This function takes a value and damages the target with that value
    * @param Damage This is the amount to damage the target by
    */
    void DamageTarget(float Damage);
	
};
