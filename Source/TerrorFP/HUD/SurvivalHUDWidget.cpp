// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "../Game/SurvivalSaveGame.h"
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

//// Called every frame
//void USurvivalHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//    Super::NativeTick( MyGeometry, InDeltaTime );
//    
//    // Prepare delay function variables
//    FLatentActionInfo LatentActionInfoSlotOne;
//    LatentActionInfoSlotOne.CallbackTarget = this;
//    LatentActionInfoSlotOne.ExecutionFunction = "PrepareSlotOneItem";
//    LatentActionInfoSlotOne.UUID = 1111;
//    LatentActionInfoSlotOne.Linkage = 0;
//    
//    // The delay function call
//    UKismetSystemLibrary::Delay(this, 0.5, LatentActionInfoSlotOne);
//
//}
//
//void USurvivalHUDWidget::PrepareSlotOneItem()
//{
//    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
//    
//    // Get Item for the upcoming switch
//    if (!Char) { return; }
//    int32 Item = Char->GetSlotOneItem();
//    
//    // Prepare Image that we will need for setting the brush
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotOneWidget = GetWidgetFromName("InvSlotOne");
//    // Cast it to an Image we can use
//    UImage* SlotOneImage = Cast<UImage>(SlotOneWidget);
//    // Get the Texture for the Image
//    static ConstructorHelpers::FObjectFinder<UTexture2D>
//    LogTexture(TEXT("/Game/SurvivalHorrorGame/LogsInvItem"));
//    
//    // Change the image
//    switch (Item)
//    {
//        case WoodID:
//        {
//            if (LogTexture.Succeeded())
//            {
//                SlotOneImage->SetBrushFromTexture(LogTexture.Object);
//                break;
//            }
//        }
//        default:
//        {
//            if (GEngine)
//                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to set Image1.png");
//            break;
//        }
//    }
//}
//
//void USurvivalHUDWidget::NativeConstruct()
//{
//    Super::NativeConstruct();
//    
//    UObject* something = StaticLoadObject(UObject::StaticClass(), nullptr, (TEXT("/Game/SurvivalHorrorGame/LogsInvItem")));
//    
//    LogTex = Cast<UTexture2D>(something);
//
//}

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

    // TODO: remove this stuff if it compiles without
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotOneWidget = GetWidgetFromName("InvSlotOne");
//    
//    // Cast it to an Image we can use
//    UImage* SlotOneImage = Cast<UImage>(SlotOneWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {

            
            break;
        }
        case WoodID:
        {
            // TODO: Figure out why this didn't work: SlotOneImage->SetBrushFromTexture(ImageTexture);
            ImageOneBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case KeyID:
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
    
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotTwoWidget = GetWidgetFromName("InvSlotTwo");
//    
//    // Cast it to an Image we can use
//    UImage* SlotTwoImage = Cast<UImage>(SlotTwoWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            
            
            break;
        }
        case WoodID:
        {
            ImageTwoBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case KeyID:
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
    
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotThreeWidget = GetWidgetFromName("InvSlotThree");
//    
//    // Cast it to an Image we can use
//    UImage* SlotThreeImage = Cast<UImage>(SlotThreeWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            
            
            break;
        }
        case WoodID:
        {
            ImageThreeBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case KeyID:
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
    
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotFourWidget = GetWidgetFromName("InvSlotFour");
//    
//    // Cast it to an Image we can use
//    UImage* SlotFourImage = Cast<UImage>(SlotFourWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            
            
            break;
        }
        case WoodID:
        {
            ImageFourBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case KeyID:
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
    
//    // Get a reference to the widget with the name InvSlotOne
//    UWidget* SlotFiveWidget = GetWidgetFromName("InvSlotFive");
//    
//    // Cast it to an Image we can use
//    UImage* SlotFiveImage = Cast<UImage>(SlotFiveWidget);
    
    
    switch (Item)
    {
        case EmptyID:
        {
            
            
            break;
        }
        case WoodID:
        {
            ImageFiveBrush.SetResourceObject(WoodImageTexture);
            break;
        }
        case KeyID:
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

