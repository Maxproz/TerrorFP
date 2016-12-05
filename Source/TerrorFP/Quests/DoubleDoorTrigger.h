// Copyright @Maxpro 2016

#pragma once

#include "Engine/TriggerBox.h"
#include "DoubleDoorTrigger.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API ADoubleDoorTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
private:
    ADoubleDoorTrigger();
	
public:
    /*This function is called when an Actor enters the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor);
    
    /*This function is called when an Actor exits the Trigger - 4.12 version*/
    UFUNCTION()
    void OnTriggerExit(AActor* OverlappedActor, AActor* OtherActor);
    
    UFUNCTION()
    void DoorsOpenedSetNextObjective(class ATP_ThirdPersonCharacter* Char);
    
protected:
    
    UPROPERTY(EditAnywhere, Category = "Quest System")
    FString NextQuest = "Enter the house";
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
    class USaveGame* SaverSubClass;
    
    // This needs to be set before runtime.
    UPROPERTY(EditAnywhere, Category = "Matinee")
    class AMatineeActor* DoubleDoorMatinee;

};
