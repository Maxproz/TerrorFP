// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TerrorFP.h"
#include "TerrorFPGameMode.h"
#include "TerrorFPHUD.h"
#include "TerrorFPCharacter.h"

ATerrorFPGameMode::ATerrorFPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATerrorFPHUD::StaticClass();
}

void ATerrorFPGameMode::DoSomething()
{
    GLog->Log("doing something");
}

void ATerrorFPGameMode::DoSomethingElse(float param)
{
    GLog->Log("Param: " + FString::SanitizeFloat(param));
}

void ATerrorFPGameMode::DoubleParamFunction(float param1, int32 param2)
{
    
    FString ErrorMsg("Param1: " + FString::SanitizeFloat(param1) + " - Param2: "+ FString::FromInt(param2));
    GLog->Log(ErrorMsg);
    
    if (GEngine)
    {
        // Display a debug message for 5 seconds
        // The -1 "Key" value (first argument) indicates that we will never need to update or refresh this msg
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple,
            ErrorMsg);
    }
}
