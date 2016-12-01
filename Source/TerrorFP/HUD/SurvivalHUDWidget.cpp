// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "SurvivalHUDWidget.h"


// TODO: Figure out why this function doesn't work for the progress bar. Make reddit post or ask orfeas
/*
float USurvivalHUDWidget::GetPercentHunger()
{
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    
    float ReturnValue = 0;
    
    if (Char != nullptr)
    {
        float CurrentHunger = UKismetMathLibrary::Conv_IntToFloat(Char->GetPlayerHunger());
        ReturnValue = UKismetMathLibrary::Divide_FloatFloat(CurrentHunger, 100);
    }
    return ReturnValue;
}
*/


float USurvivalHUDWidget::GetPercentBattery() const
{
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        return 0.0f;
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
        return 0.0f;
    
    return (float)Char->GetPlayerBattery() / 100.0f;
}