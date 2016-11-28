// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "TerrorFPGameMode.generated.h"

UCLASS(minimalapi)
class ATerrorFPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATerrorFPGameMode();
    
    virtual void BeginPlay() override;
    
    /************* CUSTOM CONSOLE COMMANDS ************/
    // Function with no parameters
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoSomething();
    
    // Function with one parameter
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoSomethingElse(float param);
    
    // Function with two parameters
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoubleParamFunction(float param1, int32 param2);
    /************* CUSTOM CONSOLE COMMANDS ************/
    
    
private:
    /************* LEVEL STREAMING CODE ************/
    // Contains all the available transforms of LevelMovePointActors.
    TArray<FTransform> Transforms;
    
    // Map name to spawn
    FString MapName;
    
    // The desired transform of our map
    FTransform MapTransform;
    
    // Spawns the desired map based on the MapName and the MapTransform
    UFUNCTION()
    void SpawnMap();
    
public:
    /** Moves or spawns a map in the BaseMap.
    * @param MapName - the name of the map we want to move
    * @param Position - the index of the Transforms array we want to use
    */
    UFUNCTION(Exec, Category = "LevelStreaming")
    void MoveMap(FString MapName, int32 Position);
    
    /************* LEVEL STREAMING CODE ************/
};



