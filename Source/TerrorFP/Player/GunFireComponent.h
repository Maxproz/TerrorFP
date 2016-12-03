// Copyright @Maxpro 2016

#pragma once

#include "Components/ActorComponent.h"
#include "GunFireComponent.generated.h"

// TODO remove this class
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRORFP_API UGunFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunFireComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
