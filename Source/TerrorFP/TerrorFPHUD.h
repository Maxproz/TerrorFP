// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "TerrorFPHUD.generated.h"

UCLASS()
class ATerrorFPHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATerrorFPHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

