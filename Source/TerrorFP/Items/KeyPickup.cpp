// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "../StaticConstantNames.h"
#include "KeyPickup.h"


// Sets default values
AKeyPickup::AKeyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
    SetRootComponent(Mesh);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> KeyVisual(TEXT("/Game/SurvivalHorrorGame/Key_B_02"));
    if (KeyVisual.Succeeded())
    { Mesh->SetStaticMesh(KeyVisual.Object); }
    
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
    BoxCollision->SetRelativeScale3D(FVector(4.6, 4.6, 4.6));
    BoxCollision->AttachToComponent(Mesh, FAttachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform));
    BoxCollision->bGenerateOverlapEvents = true;
    
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AKeyPickup::OnOverlapBegin);
    BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AKeyPickup::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AKeyPickup::BeginPlay()
{
    Super::BeginPlay();
    
    
    // Delay for making it so this item can't be picked up shortly after being dropped (AKA: "Spawned")
    FLatentActionInfo LatentActionInfoRecentDropDelay;
    LatentActionInfoRecentDropDelay.CallbackTarget = this;
    LatentActionInfoRecentDropDelay.ExecutionFunction = "RecentDropDelay";
    LatentActionInfoRecentDropDelay.UUID = 1112;
    LatentActionInfoRecentDropDelay.Linkage = 0;
    
    // The delay call
    UKismetSystemLibrary::Delay(this, 3.0, LatentActionInfoRecentDropDelay);
    
}

// Called every frame
void AKeyPickup::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

void AKeyPickup::RecentDropDelay()
{
    // The delay is finished, make it so item can be pickedup.
    bCanPickup = true;
}

void AKeyPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Starting");
    
    if (bCanPickup == true) // Executes below actions if true, does nothing otherwise.
    {
        ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
        
        
        // TODO: Refactor this junk into a for or for-each loop.
        if (bIsEmptyID(Char->GetSlotOneItem()))
        {
            Char->SetSlotOneItem(StaticConstantNames::KeyID);
            K2_DestroyActor();
        }
        else
        {
            if (bIsEmptyID(Char->GetSlotTwoItem()))
            {
                Char->SetSlotTwoItem(StaticConstantNames::KeyID);
                K2_DestroyActor();
            }
            else
            {
                if (bIsEmptyID(Char->GetSlotThreeItem()))
                {
                    Char->SetSlotThreeItem(StaticConstantNames::KeyID);
                    K2_DestroyActor();
                }
                else
                {
                    if (bIsEmptyID(Char->GetSlotFourItem()))
                    {
                        Char->SetSlotFourItem(StaticConstantNames::KeyID);
                        K2_DestroyActor();
                    }
                    else
                    {
                        if (bIsEmptyID(Char->GetSlotFiveItem()))
                        {
                            Char->SetSlotFiveItem(StaticConstantNames::KeyID);
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
        
        Char->SetPlayerHasDoubleDoorKey(true);
        
        // TODO: Call a function here to spawn emitter and sound effect.
    }
}

void AKeyPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Not using for right now.
    
    //    if (GEngine)
    //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pickup Item Overlap Ending");
}