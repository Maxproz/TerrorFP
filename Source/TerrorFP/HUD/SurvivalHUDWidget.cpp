// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "../Game/SurvivalSaveGame.h"
//#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "../StaticConstantNames.h"
#include "SurvivalHUDWidget.h"


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

USurvivalHUDWidget::USurvivalHUDWidget(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> WoodTex(TEXT("/Game/SurvivalHorrorGame/LogsInvItem"));
    WoodImageTexture = WoodTex.Object;
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> KeyTex(TEXT("/Game/SurvivalHorrorGame/KeyInvItem"));
    KeyImageTexture = KeyTex.Object;
    
    // TODO: Implement default image and additional image stuff here.
    
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
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {

            
            break;
        }
        case StaticConstantNames::WoodID:
        {
            // TODO: Figure out why this didn't work: SlotOneImage->SetBrushFromTexture(ImageTexture);
            ImageOneBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            ImageOneBrush.SetResourceObject(KeyImageTexture);
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
    
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            
            
            break;
        }
        case StaticConstantNames::WoodID:
        {
            ImageTwoBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            ImageTwoBrush.SetResourceObject(KeyImageTexture);
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
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            
            break;
        }
        case StaticConstantNames::WoodID:
        {
            ImageThreeBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            ImageThreeBrush.SetResourceObject(KeyImageTexture);
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
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            
            break;
        }
        case StaticConstantNames::WoodID:
        {
            ImageFourBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            ImageFourBrush.SetResourceObject(KeyImageTexture);
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
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            
            break;
        }
        case StaticConstantNames::WoodID:
        {
            ImageFiveBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            ImageFiveBrush.SetResourceObject(KeyImageTexture);
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

FText USurvivalHUDWidget::GetCurrentObjective() const
{
    if (UGameplayStatics::DoesSaveGameExist(ATP_ThirdPersonCharacter::PlayerSaveSlot, 0))
    {
        USaveGame* SaverSubClass = UGameplayStatics::LoadGameFromSlot(
                                                                ATP_ThirdPersonCharacter::PlayerSaveSlot, 0);
        USurvivalSaveGame* SurvivalSaveGame = Cast<USurvivalSaveGame>(SaverSubClass);
        FText CurrentObjText = SurvivalSaveGame->GetPlayerObjective();
        return CurrentObjText;
    }
    else
    {
        // TODO: for now, assuming starting quest text if no saved game state. Change to come from player
        // TODO: Was getting the first quest text from a default initalized non pointer really,
        //       - what was causing the crash I was getting?
        FText ReturnText = FText::FromString("Collect Firewood");
        return ReturnText;
    }
}

