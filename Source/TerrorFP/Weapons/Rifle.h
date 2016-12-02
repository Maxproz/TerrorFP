// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class TERRORFP_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
