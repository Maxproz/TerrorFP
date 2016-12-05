// Copyright @Maxpro 2016

#pragma once

#include "Engine/TriggerVolume.h"
#include "CampfireTriggerVolume.generated.h"

/**
 *  TODO: Bug causes this call to have no colision volume after compilation sometimes, need a fix.
 *  TODO: Probably can just remake this class using a TriggerBox
 */
UCLASS()
class TERRORFP_API ACampfireTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

private:
    
    ACampfireTriggerVolume();
    
public:
    /*This function is called when an Actor enters the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor);
    
    /*This function is called when an Actor exits the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerExit(AActor* OverlappedActor, AActor* OtherActor);
	
    
    UFUNCTION()
    void SetNextObjectiveForPlayer(class ATP_ThirdPersonCharacter* Char);
    
    // TODO: How can I get this shared across files?
    // TODO: nevermind its static inside the TPPlayer but how can I make it a UPropery EditAnywhere in there?
    // const FString SlotName = "SurvivalSaveGame";
    
    // TODO: Should this be public?
    void HandlePlayersWood(class ATP_ThirdPersonCharacter* Char);
    
protected:
    
    // Don't need to initalize this since it's 100% going to be set using a branch if-else later on.
    UPROPERTY(EditAnywhere, Category = "Quest System")
    FString NextQuest;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
    class USaveGame* SaverSubClass;
    
    UPROPERTY(EditAnywhere, Category = "Matinee")
    class AMatineeActor* CampfireCompleteMatinee;
    
};
