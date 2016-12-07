// Copyright @Maxpro 2016

#pragma once

#include "Blueprint/UserWidget.h"
#include "InstructionalWidget.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API UInstructionalWidget : public UUserWidget
{
	GENERATED_BODY()
	

	
public:
    UInstructionalWidget(const FObjectInitializer& ObjectInitializer);
    
    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void PlayAnimationDelay();
    
    
    UWidgetAnimation* WidgetAnim;
    
    void AssignAnimations();
};
