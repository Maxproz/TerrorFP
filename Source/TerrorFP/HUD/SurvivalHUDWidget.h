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
    class UTexture2D* WoodImageTexture;
    
    UPROPERTY()
    class UTexture2D* KeyImageTexture;
    
    // TODO: Implement this once you got a good default texture
    // UPROPERTY()
    //class UTexture2D* EmptyImageTexture;
    
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
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FText GetCurrentObjective() const;
    
    
//    // Called every frame
//    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
//    
//    void PrepareSlotOneItem();
};
