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
	
private:
//    virtual void NativeConstruct() override;
    
public:
    
    USurvivalHUDWidget(const FObjectInitializer& ObjectInitializer);
//    UFUNCTION(BlueprintPure, Category = "HUD")
//	float GetPercentHunger();
	
    UPROPERTY()
    class UTexture2D* ImageTexture;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    float GetPercentBattery() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetItemOneImage() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetItemTwoImage() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetItemThreeImage() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetItemFourImage() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetItemFiveImage() const;
    
    
    
//    // Called every frame
//    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
//    
//    void PrepareSlotOneItem();
};
