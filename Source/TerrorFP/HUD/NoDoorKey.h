// Copyright @Maxpro 2016

#pragma once

#include "Blueprint/UserWidget.h"
#include "NoDoorKey.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API UNoDoorKey : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UNoDoorKey(const FObjectInitializer& ObjectInitializer);
    
    UPROPERTY()
    class UTexture2D* KeyImageTexture;
    
    UFUNCTION(BlueprintPure, Category = "HUD")
    FSlateBrush GetKeyPopupImage() const;
    
    virtual void NativeConstruct() override;
    
//    UWidget* FirstBanner;
    UWidgetAnimation* WidgetAnim;
    
    void AssignAnimations();
};

