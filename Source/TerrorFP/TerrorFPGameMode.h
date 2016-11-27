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
    
    // Function with no parameters
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoSomething();
    
    // Function with one parameter
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoSomethingElse(float param);
    
    // Function with two parameters
    UFUNCTION(Exec, Category = "ExecFunctions")
    void DoubleParamFunction(float param1, int32 param2);
};



