// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
//#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "SurvivalHUDWidget.h"

// TODO: move these to a separate file and include it.
const int32 EmptyID = 0;     // White
const int32 WoodID = 1;      // Blue
const int32 KeyID = 2;       // Purple
const int32 TinderBoxID = 3; // Green

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
    {
        return 0.0f;
    }
    
    return (float)Char->GetPlayerBattery() / 100.0f;
}

FSlateBrush USurvivalHUDWidget::GetItemOneImage() const
{
    // The brush we will return
    FSlateBrush ImageOneBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    // Get the Item we will use to switch on.
    int32 Item = Char->GetSlotOneItem();
    
    // Get a reference to the widget with the name InvSlotOne
    UWidget* SlotOneWidget = GetWidgetFromName("InvSlotOne");
    
    // Cast it to an Image we can use
    UImage* SlotOneImage = Cast<UImage>(SlotOneWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            // We are showing Empty as white for now.
            SlotOneImage->SetColorAndOpacity(FLinearColor::White);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::White;
            
            break;
        }
        case WoodID:
        {
            // We are showing Wood as Blue for now.
            SlotOneImage->SetColorAndOpacity(FLinearColor::Blue);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::Blue;
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to get valid Item ID: Image1");
            break;
        }
    }
    
    return ImageOneBrush;
}


FSlateBrush USurvivalHUDWidget::GetItemTwoImage() const
{
    // The brush we will return
    FSlateBrush ImageTwoBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    // Get the Item we will use to switch on.
    int32 Item = Char->GetSlotTwoItem();
    
    // Get a reference to the widget with the name InvSlotOne
    UWidget* SlotTwoWidget = GetWidgetFromName("InvSlotTwo");
    
    // Cast it to an Image we can use
    UImage* SlotTwoImage = Cast<UImage>(SlotTwoWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            // We are showing Empty as white for now.
            SlotTwoImage->SetColorAndOpacity(FLinearColor::White);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::White;
            
            break;
        }
        case WoodID:
        {
            // We are showing Wood as Blue for now.
            SlotTwoImage->SetColorAndOpacity(FLinearColor::Blue);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::Blue;
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to get valid Item ID: Image2");
            break;
        }
    }
    
    
    return ImageTwoBrush;
}

FSlateBrush USurvivalHUDWidget::GetItemThreeImage() const
{
    // The brush we will return
    FSlateBrush ImageThreeBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    // Get the Item we will use to switch on.
    int32 Item = Char->GetSlotThreeItem();
    
    // Get a reference to the widget with the name InvSlotOne
    UWidget* SlotThreeWidget = GetWidgetFromName("InvSlotThree");
    
    // Cast it to an Image we can use
    UImage* SlotThreeImage = Cast<UImage>(SlotThreeWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            // We are showing Empty as white for now.
            SlotThreeImage->SetColorAndOpacity(FLinearColor::White);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::White;
            
            break;
        }
        case WoodID:
        {
            // We are showing Wood as Blue for now.
            SlotThreeImage->SetColorAndOpacity(FLinearColor::Blue);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::Blue;
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to get valid Item ID: Image2");
            break;
        }
    }
    
    
    return ImageThreeBrush;
}

FSlateBrush USurvivalHUDWidget::GetItemFourImage() const
{
    // The brush we will return
    FSlateBrush ImageFourBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    // Get the Item we will use to switch on.
    int32 Item = Char->GetSlotFourItem();
    
    // Get a reference to the widget with the name InvSlotOne
    UWidget* SlotFourWidget = GetWidgetFromName("InvSlotFour");
    
    // Cast it to an Image we can use
    UImage* SlotFourImage = Cast<UImage>(SlotFourWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            // We are showing Empty as white for now.
            SlotFourImage->SetColorAndOpacity(FLinearColor::White);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::White;
            
            break;
        }
        case WoodID:
        {
            // We are showing Wood as Blue for now.
            SlotFourImage->SetColorAndOpacity(FLinearColor::Blue);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::Blue;
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to get valid Item ID: Image2");
            break;
        }
    }
    
    
    return ImageFourBrush;
}

FSlateBrush USurvivalHUDWidget::GetItemFiveImage() const
{
    // The brush we will return
    FSlateBrush ImageFiveBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        // Should we return something else here?
        return FSlateBrush();
    }
    
    // Get the Item we will use to switch on.
    int32 Item = Char->GetSlotFiveItem();
    
    // Get a reference to the widget with the name InvSlotOne
    UWidget* SlotFiveWidget = GetWidgetFromName("InvSlotFive");
    
    // Cast it to an Image we can use
    UImage* SlotFiveImage = Cast<UImage>(SlotFiveWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            // We are showing Empty as white for now.
            SlotFiveImage->SetColorAndOpacity(FLinearColor::White);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::White;
            
            break;
        }
        case WoodID:
        {
            // We are showing Wood as Blue for now.
            SlotFiveImage->SetColorAndOpacity(FLinearColor::Blue);
            
            // TODO: Keep this in until we need to set the image.
            // ImageOneBrush.TintColor = FLinearColor::Blue;
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to get valid Item ID: Image2");
            break;
        }
    }
    
    
    return ImageFiveBrush;
}

