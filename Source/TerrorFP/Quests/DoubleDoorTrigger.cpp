// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Matinee/MatineeActor.h"
#include "../Game/SurvivalSaveGame.h"
#include "Kismet/KismetStringLibrary.h"
#include "DoubleDoorTrigger.h"


ADoubleDoorTrigger::ADoubleDoorTrigger()
{
    //Register the enter and exit overlaps to fire
    OnActorBeginOverlap.AddDynamic(this, &ADoubleDoorTrigger::OnTriggerEnter);
    OnActorEndOverlap.AddDynamic(this, &ADoubleDoorTrigger::OnTriggerExit);
}

/*4.12 version*/
void ADoubleDoorTrigger::OnTriggerEnter(AActor* OverlapedActor, AActor* OtherActor)
{
    // Cast to the player character so we can read the has key variable for the door.
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    
    // Play the matinee
    if (!DoubleDoorMatinee)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Missing Matinee for doubledoors"));
    
    if (Char && Char->GetPlayerHasDoubleDoorKey() == true)
    {
        DoubleDoorMatinee->Play();
        DoorsOpenedSetNextObjective(Char);
    }
    else
    {
        // Add a popup to the players screen here saying "You do not have the key" or something
        
        
    }
}

/*4.12 version*/
void ADoubleDoorTrigger::OnTriggerExit(AActor* OverlapedActor, AActor* OtherActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("End overlap has fired"));
    }
}


void ADoubleDoorTrigger::DoorsOpenedSetNextObjective(ATP_ThirdPersonCharacter* Char)
{
    
    Char->PlayerObjective = NextQuest;
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