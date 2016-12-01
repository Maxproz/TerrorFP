// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "WoodInvPickup.h"


// TODO: move these to a separate file and include it. Make them static const?
const int32 EmptyID = 0;     // White
const int32 WoodID = 1;      // Blue
const int32 KeyID = 2;       // Purple
const int32 TinderBoxID = 3; // Green

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
    
    // Set material of the cube
    static ConstructorHelpers::FObjectFinder<UMaterial> CubeVisualAssetMaterial(TEXT("/Game/SurvivalHorrorGame/LogsInvItem"));
    if (CubeVisualAsset.Succeeded())
    {
        Cube->SetMaterial(0, CubeVisualAssetMaterial.Object);
    }
    
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
	
}

// Called every frame
void AWoodInvPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWoodInvPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Starting");
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    
    
    // TODO: Refactor this junk into a for or for-each loop.
    if (bIsEmptyID(Char->GetSlotOneItem()))
    {
        Char->SetSlotOneItem(WoodID);
        K2_DestroyActor();
    }
    else
    {
        if (bIsEmptyID(Char->GetSlotTwoItem()))
        {
            Char->SetSlotTwoItem(WoodID);
            K2_DestroyActor();
        }
        else
        {
            if (bIsEmptyID(Char->GetSlotThreeItem()))
            {
                Char->SetSlotThreeItem(WoodID);
                K2_DestroyActor();
            }
            else
            {
                if (bIsEmptyID(Char->GetSlotFourItem()))
                {
                    Char->SetSlotFourItem(WoodID);
                    K2_DestroyActor();
                }
                else
                {
                    if (bIsEmptyID(Char->GetSlotFiveItem()))
                    {
                        Char->SetSlotFiveItem(WoodID);
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
    
    //  TODO: Can we need to destroy the actor just once here after pickup?
    // K2_DestroyActor();
    
    // TODO: Call a function here to spawn emitter and sound effect.
    
}

void AWoodInvPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Not using for right now.
    
    //    if (GEngine)
    //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Ending");
}
