// Copyright @Maxpro 2016

#pragma once

#include "Blueprint/UserWidget.h"
#include "ObjectiveComplete.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API UObjectiveComplete : public UUserWidget
{
	GENERATED_BODY()
	
    
public:
    UObjectiveComplete(const FObjectInitializer& ObjectInitializer);
    //    UFUNCTION(BlueprintPure, Category = "HUD")
    //	float GetPercentHunger();
    
    UPROPERTY()
    class UTexture2D* ObjCompleteBanner;
	
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetFirstCompleteBanner() const;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FLinearColor MakeBannersTransparent() const;
    
    virtual void NativeConstruct() override;
    
    
    UWidget* FirstBanner;
    
    UWidgetAnimation* WidgetAnim;
    
    
    
    void AssignAnimations();
//    UObject* Img = ImageOneBrush.GetResourceObject();
//    UImage* SlotOneImage = Cast<UImage>(Img);
//    SlotOneImage->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
};
