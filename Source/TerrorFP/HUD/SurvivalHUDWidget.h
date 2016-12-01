// Copyright @Maxpro 2016

#pragma once

#include "Blueprint/UserWidget.h"
#include "SurvivalHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API USurvivalHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
//    UFUNCTION(BlueprintPure, Category = "HUD")
//	float GetPercentHunger();
	
    UFUNCTION(BlueprintPure, Category = "HUD")
    float GetPercentBattery() const;
    
};
