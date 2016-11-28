// Copyright @Maxpro 2016

#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponBackpackItem.generated.h"

USTRUCT()
struct FWeaponBackpackItem
{
    GENERATED_USTRUCT_BODY()
    
    // Which weapon should be spawned
    AActor* WeaponToSpawn;
    
    // Image in weapon select
    UTexture2D* BackpackImage;
    
    // Is this weapon currently selected
    bool bIsSelected;
    
    // In which slot is this weapon;
    int32 InSlot;
};