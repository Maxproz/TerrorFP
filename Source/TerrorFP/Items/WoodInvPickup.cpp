// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../HUD/ObjectiveComplete.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "../Game/SurvivalSaveGame.h"
#include "Kismet/KismetStringLibrary.h"
#include "../StaticConstantNames.h"
#include "WoodInvPickup.h"


const int32 AddOneWood = 1;

// Sets default values
AWoodInvPickup::AWoodInvPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    SetRootComponent(Cube);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/SurvivalHorrorGame/Logs_Mesh"));
    if (CubeVisualAsset.Succeeded())
    {
        Cube->SetStaticMesh(CubeVisualAsset.Object);
        
        // To change the mesh location in case I need to later.
        //Cube->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        //Cube->SetWorldScale3D(FVector(0.8f));
    }
    
//    // Set material of the cube
//    static ConstructorHelpers::FObjectFinder<UMaterial> CubeVisualAssetMaterial(TEXT("/Game/SurvivalHorrorGame/LogsInvItem"));
//    if (CubeVisualAsset.Succeeded())
//    {
//        Cube->SetMaterial(0, CubeVisualAssetMaterial.Object);
//    }
    
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
    BoxCollision->SetRelativeScale3D(FVector(4.6, 4.6, 4.6));
    BoxCollision->AttachToComponent(Cube, FAttachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform));
    BoxCollision->bGenerateOverlapEvents = true;
    
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWoodInvPickup::OnOverlapBegin);
    BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AWoodInvPickup::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AWoodInvPickup::BeginPlay()
{
	Super::BeginPlay();
	
    
    // Delay for making it so this item can't be picked up shortly after being dropped (AKA: "Spawned")
    FLatentActionInfo LatentActionInfoRecentDropDelay;
    LatentActionInfoRecentDropDelay.CallbackTarget = this;
    LatentActionInfoRecentDropDelay.ExecutionFunction = "RecentDropDelay";
    LatentActionInfoRecentDropDelay.UUID = 1240;
    LatentActionInfoRecentDropDelay.Linkage = 0;
    
    // The delay call
    UKismetSystemLibrary::Delay(this, 3.0, LatentActionInfoRecentDropDelay);
    
}

// Called every frame
void AWoodInvPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWoodInvPickup::RecentDropDelay()
{
    // The delay is finished, make it so item can be pickedup.
    bCanPickup = true;
}

void AWoodInvPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Starting");
    
    if (bCanPickup == true) // Executes below actions if true, does nothing otherwise.
    {
        ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
        
        
        // TODO: Refactor this junk into a for or for-each loop.
        if (bIsEmptyID(Char->GetSlotOneItem()))
        {
            Char->SetSlotOneItem(StaticConstantNames::WoodID);
            K2_DestroyActor();
        }
        else
        {
            if (bIsEmptyID(Char->GetSlotTwoItem()))
            {
                Char->SetSlotTwoItem(StaticConstantNames::WoodID);
                K2_DestroyActor();
            }
            else
            {
                if (bIsEmptyID(Char->GetSlotThreeItem()))
                {
                    Char->SetSlotThreeItem(StaticConstantNames::WoodID);
                    K2_DestroyActor();
                }
                else
                {
                    if (bIsEmptyID(Char->GetSlotFourItem()))
                    {
                        Char->SetSlotFourItem(StaticConstantNames::WoodID);
                        K2_DestroyActor();
                    }
                    else
                    {
                        if (bIsEmptyID(Char->GetSlotFiveItem()))
                        {
                            Char->SetSlotFiveItem(StaticConstantNames::WoodID);
                            K2_DestroyActor();
                        }
                        else
                        {
                            // Inform Character that inventory is full.
                            // Maybe call a function from SurviorHUDWidget
                            // - to have a string widget appear momentarily.
                            if (GEngine)
                                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, "Inventory is Full");
                        }
                    }
                }
            }
        }
        
        Char->SetNumberOfWood(AddOneWood);
        
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                                         "Player Log Amount: " + FString::FromInt(Char->GetNumberOfWood()));
        
        if (Char->GetNumberOfWood() >= 3)
        {
//    Char->WidgetInstanceObjComplete = CreateWidget<UObjectiveComplete>(UGameplayStatics::GetPlayerController(Char, 0));
            Char->WidgetInstanceObjComplete->SetIsEnabled(true);
            Char->WidgetInstanceObjComplete->AddToViewport();
            SetNextQuest(Char);
        }
        
        
        //  TODO: Can we need to destroy the actor just once here after pickup?
        // K2_DestroyActor();
        
        // TODO: Call a function here to spawn emitter and sound effect.
    }
}

void AWoodInvPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Not using for right now.
    
    //    if (GEngine)
    //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Ending");
}

void AWoodInvPickup::SetNextQuest(ATP_ThirdPersonCharacter* Char)
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

