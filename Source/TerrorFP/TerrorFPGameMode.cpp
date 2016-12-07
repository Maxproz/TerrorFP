// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TerrorFP.h"
#include "TerrorFPGameMode.h"
#include "TerrorFPHUD.h"
#include "TerrorFPCharacter.h"
#include "Level/LevelMovePoint.h"

ATerrorFPGameMode::ATerrorFPGameMode()
	: Super()
{
    // TODO: change this to our updated character?
    
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

    
    // TODO: Can update this inorder to modify the HUD in the future.
    
	// use our custom HUD class
	HUDClass = ATerrorFPHUD::StaticClass();
}

void ATerrorFPGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    TArray<AActor*> OutActors;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelMovePoint::StaticClass(), OutActors);
    
    for (auto It : OutActors)
    {
        // Get the transform of each actor
        Transforms.Add(It->GetTransform());
    }
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

void ATerrorFPGameMode::SpawnMap()
{
    FLatentActionInfo info;
    
    //We load the stream level but we make sure not to make it visible before we assign a transform to it
    //The reason I've typed *MapName is the parameters is because the second parameters needs an FName so
    //essentially I'm type casting the FString to FName
    UGameplayStatics::LoadStreamLevel(GetWorld(), *MapName, false, false, info);
    ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(GetWorld(), *MapName);
    
    // Assign a new transform to our level
    level->LevelTransform = MapTransform;
    
    // Make the level visible
    level->bShouldBeVisible = true;
}

void ATerrorFPGameMode::MoveMap(FString MapName, int32 Position)
{
    if (Transforms.IsValidIndex(Position))
    {
        ULevelStreaming* level = UGameplayStatics::GetStreamingLevel(GetWorld(), *MapName);
        
        //store the new map name and the new transform
        this->MapName = MapName;
        MapTransform = Transforms[Position];
        
        if (level->IsLevelVisible())
        {
            //If the level is visible we need to unload it first
            //and then spawn it in a new location
            
            //The unload stream level is essentially an async operation
            //Using the Latent Action Info we're able to create a callback
            //which is fired when the UnloadStreamLevel finishes its execution
            FLatentActionInfo info;
            info.CallbackTarget = this;
            info.ExecutionFunction = FName("SpawnMap");
            info.UUID = 2312;
            info.Linkage = 1;
            
            UGameplayStatics::UnloadStreamLevel(GetWorld(), *MapName, info);
        }
        //If the level is not visible just spawn the map
        else SpawnMap();
    }
}