// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "ChangeLevel.generated.h"

UCLASS()
class TERRORFP_API AChangeLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChangeLevel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(BlueprintAssignable, Category ="Collision" )
    FComponentBeginOverlapSignature OnComponentBeginOverlap;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UStaticMeshComponent* StaticMeshComp;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    class UParticleSystemComponent* ParticleSystem;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* BoxCollider;
    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
