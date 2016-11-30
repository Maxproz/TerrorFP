// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "../Game/SurvivalSaveGame.h"
#include "ObjectiveChange.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AObjectiveChange::AObjectiveChange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
    BoxCollider->bGenerateOverlapEvents = true;


    //Register the enter and exit overlaps to fire
    OnActorBeginOverlap.AddDynamic(this, &AObjectiveChange::OnTriggerEnter);
    OnActorEndOverlap.AddDynamic(this, &AObjectiveChange::OnTriggerExit);
}

// Called when the game starts or when spawned
void AObjectiveChange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectiveChange::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

/*4.12 version*/
void AObjectiveChange::OnTriggerEnter(AActor* OverlapedActor, AActor* OtherActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Begin overlap has fired"));
        
        ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
        if (Char)
        {
            Char->PlayerObjective = NextQuest;
            if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
            {
                // TODO: Filter out into function
                // If it does exist
                SaverSubClass = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
                
                USurvivalSaveGame* SurvivalSaveGame = Cast<USurvivalSaveGame>(SaverSubClass);
                
                SurvivalSaveGame->SetPlayerObjective(FText::FromString(NextQuest));
                
                bool save = UGameplayStatics::SaveGameToSlot(SaverSubClass, SlotName, 0);

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
                
                bool save = UGameplayStatics::SaveGameToSlot(SaverSubClass, SlotName, 0);
                
                if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, "Save success ? " +
                                                     UKismetStringLibrary::Conv_BoolToString(save));
            }
        }
    }
}

/*4.12 version*/
void AObjectiveChange::OnTriggerExit(AActor* OverlapedActor, AActor* OtherActor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("End overlap has fired"));
    }
}
