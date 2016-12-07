// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "ObjectiveChange.h" // TODO: Probably can remove this
#include "../Game/SurvivalSaveGame.h"
#include "CampfireTriggerVolume.h"
#include "../HUD/ObjectiveComplete.h" // for obj complete banner
#include "Matinee/MatineeActor.h"
#include "../StaticConstantNames.h"
#include "Kismet/KismetStringLibrary.h"


ACampfireTriggerVolume::ACampfireTriggerVolume()
{
    //Register the enter and exit overlaps to fire
    OnActorBeginOverlap.AddDynamic(this, &ACampfireTriggerVolume::OnTriggerEnter);
    OnActorEndOverlap.AddDynamic(this, &ACampfireTriggerVolume::OnTriggerExit);
}

/*4.12 version*/
void ACampfireTriggerVolume::OnTriggerEnter(AActor* OverlapedActor, AActor* OtherActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Begin overlap has fired"));
        
        ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
        if (Char)
        {
            if (Char->GetNumberOfWood() == 3 && Char->GetHasPlayerLitCampfire() == false)
            {
                Char->SetPlayerHasLitCampfire(true);
                
                SetNextObjectiveForPlayer(Char);
                
                // Active objective complete banner again
                Char->WidgetInstanceObjComplete->SetIsEnabled(true);
                Char->WidgetInstanceObjComplete->AddToViewport();
                
                UWidgetAnimation* Anim = Char->WidgetInstanceObjComplete->WidgetAnim;
                Char->WidgetInstanceObjComplete->PlayAnimation(Anim);
                // TODO: Do I need to set pointers like Anim to nullptr here?
                // ----- Or does ue4 take care of that for me?
            
                // Play the matinee
                if (!CampfireCompleteMatinee) { return; }
                CampfireCompleteMatinee->Play();

                HandlePlayersWood(Char);
            }
            else
            {
                // TODO: Maybe add a message pop-up here saying "Not enough firewood or something"
            }
        }
    }
}

void ACampfireTriggerVolume::HandlePlayersWood(ATP_ThirdPersonCharacter* Char)
{
    
    // It only takes 3 wood to build a fire, use this to track 3 subtracted from player
    int32 WoodSubtracted = 0;
    while (WoodSubtracted > -3)
    {
        if (Char->GetSlotOneItem() == StaticConstantNames::WoodID)
        {
            Char->SetSlotOneItem(StaticConstantNames::EmptyID);
            WoodSubtracted--;
        }
        else
        {
            if (Char->GetSlotTwoItem() == StaticConstantNames::WoodID)
            {
                Char->SetSlotTwoItem(StaticConstantNames::EmptyID);
                WoodSubtracted--;
            }
            else
            {
                if (Char->GetSlotThreeItem() == StaticConstantNames::WoodID)
                {
                    Char->SetSlotThreeItem(StaticConstantNames::EmptyID);
                    WoodSubtracted--;
                }
                else
                {
                    if (Char->GetSlotFourItem() == StaticConstantNames::WoodID)
                    {
                        Char->SetSlotFourItem(StaticConstantNames::EmptyID);
                        WoodSubtracted--;
                    }
                    else
                    {
                        if (Char->GetSlotFiveItem() == StaticConstantNames::WoodID)
                        {
                            Char->SetSlotFiveItem(StaticConstantNames::EmptyID);
                            WoodSubtracted--;
                        }
                        else
                        {
                            if (GEngine)
                                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, "HandlePlayerWood failed");
                        }
                    }
                }
            }
        }
    }
    
    Char->SetNumberOfWood(WoodSubtracted);
}

/*4.12 version*/
void ACampfireTriggerVolume::OnTriggerExit(AActor* OverlapedActor, AActor* OtherActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("End overlap has fired"));
    }
}

void ACampfireTriggerVolume::SetNextObjectiveForPlayer(ATP_ThirdPersonCharacter* Char)
{
    if (Char->GetPlayerHasDoubleDoorKey())
    {
        NextQuest = "Open the door.";
    }
    else
    {
        NextQuest = "Find the key and open the door";
    }
    
    Char->PlayerObjective = NextQuest; // TODO: Why Am I not using a function to set this nextquest variable?
    if (UGameplayStatics::DoesSaveGameExist(ATP_ThirdPersonCharacter::PlayerSaveSlot, 0))
    {
        // TODO: Filter out into function
        // If it does exist
        SaverSubClass = (UGameplayStatics::LoadGameFromSlot(ATP_ThirdPersonCharacter::PlayerSaveSlot, 0));
        
        USurvivalSaveGame* SurvivalSaveGame = Cast<USurvivalSaveGame>(SaverSubClass);
        
        SurvivalSaveGame->SetPlayerObjective(FText::FromString(NextQuest));
        
        bool save = UGameplayStatics::SaveGameToSlot(SaverSubClass, ATP_ThirdPersonCharacter::PlayerSaveSlot, 0);
        
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, "Save success ? " +
                                             UKismetStringLibrary::Conv_BoolToString(save));
        
    }
    else
    {
        // TODO: Filter out into function
        // If there is no save game.
        SaverSubClass = UGameplayStatics::CreateSaveGameObject(USurvivalSaveGame::StaticClass());
        
        USurvivalSaveGame* SurvivalSaveGame = Cast<USurvivalSaveGame>(SaverSubClass);
        
        SurvivalSaveGame->SetPlayerObjective(FText::FromString(NextQuest));
        
        bool save = UGameplayStatics::SaveGameToSlot(SaverSubClass, ATP_ThirdPersonCharacter::PlayerSaveSlot, 0);
        
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, "Save success ? " +
                                             UKismetStringLibrary::Conv_BoolToString(save));
    }
}