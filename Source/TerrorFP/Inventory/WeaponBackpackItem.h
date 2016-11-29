// Copyright @Maxpro 2016

#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponBackpackItem.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBackpackItem
{
    GENERATED_USTRUCT_BODY()
    
    // Which weapon should be spawned
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeapBPItem Struct")
    AActor* WeaponToSpawn;
    
    // Image in weapon select
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeapBPItem Struct")
    UTexture2D* BackpackImage;
    
    // Is this weapon currently selected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeapBPItem Struct")
    bool bIsSelected;
    
    // In which slot is this weapon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeapBPItem Struct")
    int32 InSlot;
    
    FWeaponBackpackItem()
    {
        // Always initialize your USTRUCT variables!
        //  - exception is if you know the variable type has its own default constructor
        WeaponToSpawn = nullptr;
        BackpackImage = nullptr;
        bIsSelected = false;
        InSlot = 0;
    }
    
    //Get
    AActor* GetWeaponToSpawn()
    {
        return WeaponToSpawn;
    }
    
    UTexture2D* GetBackpackImage()
    {
        return BackpackImage;
    }
    
    //Set
    void SetSlot(const int32 newSlot)
    {
        InSlot = newSlot;
    }
};