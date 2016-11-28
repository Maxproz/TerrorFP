// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "LevelMovePoint.generated.h"

UCLASS()
class TERRORFP_API ALevelMovePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelMovePoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
