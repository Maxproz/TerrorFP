// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/SaveGame.h"
#include "SurvivalSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API USurvivalSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    FText GetPlayerObjective() { return PlayerObjective; }
    
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    void SetPlayerObjective(FText Objective) { PlayerObjective = Objective; }
    
private:
    // TODO: Should this be EditAnywhere? What about a pointer?
	UPROPERTY(EditAnywhere, Category = "Save Game")
	FText PlayerObjective;

};
