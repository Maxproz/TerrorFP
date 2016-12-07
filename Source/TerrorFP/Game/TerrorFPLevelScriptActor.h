// Copyright @Maxpro 2016

#pragma once

#include "Engine/LevelScriptActor.h"
#include "TerrorFPLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class TERRORFP_API ATerrorFPLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
    
public:

    virtual void BeginPlay() override;
    
    // Widget to create and add to viewport on beginplay
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<class UInstructionalWidget> WidgetInstructionalTemplate;

    // TODO: Should this be public?
    class UInstructionalWidget* InstructionWidget;

    
};
