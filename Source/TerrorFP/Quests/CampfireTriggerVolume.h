// Copyright @Maxpro 2016

#pragma once

#include "Engine/TriggerVolume.h"
#include "CampfireTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API ACampfireTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	ACampfireTriggerVolume();
	
public:
    /*This function is called when an Actor enters the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor);
    
    /*This function is called when an Actor exits the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerExit(AActor* OverlappedActor, AActor* OtherActor);
	
    
    UFUNCTION()
    void SetCampfireObjective(class ATP_ThirdPersonCharacter* Char);
    
    // TODO: How can I get this shared across files?
    // TODO: nevermind its static inside the TPPlayer but how can I make it a UPropery EditAnywhere in there?
    // const FString SlotName = "SurvivalSaveGame";
    
protected:
    
    UPROPERTY(EditAnywhere, Category = "Quest System")
    FString NextQuest;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
    USaveGame* SaverSubClass;
    
};
