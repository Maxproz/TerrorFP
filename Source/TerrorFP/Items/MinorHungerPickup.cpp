// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "MinorHungerPickup.h"


// Sets default values
AMinorHungerPickup::AMinorHungerPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    SetRootComponent(Cube);
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeVisualAsset.Succeeded())
    {
        Cube->SetStaticMesh(CubeVisualAsset.Object);
        
        // To change the mesh location in case I need to later.
        //Cube->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        //Cube->SetWorldScale3D(FVector(0.8f));
    }

    // Set material of the cube
    static ConstructorHelpers::FObjectFinder<UMaterial> CubeVisualAssetMaterial(TEXT("/Game/Textures/MinorPickup_Diffuse_Mat"));
    if (CubeVisualAsset.Succeeded())
    {
        Cube->SetMaterial(0, CubeVisualAssetMaterial.Object);
    }
    
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
    BoxCollision->SetRelativeScale3D(FVector(2.0, 2.0, 2.0));
    BoxCollision->AttachToComponent(Cube, FAttachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform));
    BoxCollision->bGenerateOverlapEvents = true;
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMinorHungerPickup::OnOverlapBegin);
    BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMinorHungerPickup::OnOverlapEnd);
    
    
    // TODO: Figure out the difference between ActorOverlap and component Overlap
    // Register the enter and exit overlaps to fire
    // OnActorBeginOverlap.AddDynamic(this, &AMinorHungerPickup::OnTriggerEnter);
    // OnActorEndOverlap.AddDynamic(this, &AMinorHungerPickup::OnTriggerExit);
    
    
}

// Called when the game starts or when spawned
void AMinorHungerPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinorHungerPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

///*4.12 version*/
//void AMinorHungerPickup::OnTriggerEnter(AActor* OverlapedActor, AActor* OtherActor)
//{
//    GLog->Log("Begin overlap has fired");
//    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
//    
//    Char->MinorHungerPickup(25);
//    
//    // If health is greater than 100 set it to 100
//    if (Char->GetPlayerHunger() > 100)
//    {
//        GLog->Log("Player Hunger MAX: Set to 100" + FString::FromInt(Char->GetPlayerHunger()));
//        Char->PlayerHunger = 100;
//    }
//    else
//    {
//        // Temp debug msg
//        GLog->Log("Player Hunger set to " + FString::FromInt(Char->GetPlayerHunger()));
//
//    }
//}
//
///*4.12 version*/
//void AMinorHungerPickup::OnTriggerExit(AActor* OverlapedActor, AActor* OtherActor)
//{
//    GLog->Log("End overlap has fired");
//}

void AMinorHungerPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Overlap Starting");
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    
    // TODO: Add a variable to remove this magic number See BatteryPickup for reference
    Char->MinorHungerPickup(25);
    
    // If health is greater than 100 set it to 100.
    // TODO: Add a const variable to represent max hunger.
    if (Char->GetPlayerHunger() > 100)
    {
        // TODO: Add a const variable to represent max hunger. See BatteryPickup for reference
        Char->PlayerHunger = 100;
        

        if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
                "Player Hunger MAX reached! Set to: " + FString::FromInt(Char->GetPlayerHunger()));
    }
    else
    {
        // Temp debug msg
        //GLog->Log("Player Hunger set to " + FString::FromInt(Char->GetPlayerHunger()));
        if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
                    "Player Hunger set to " + FString::FromInt(Char->GetPlayerHunger()));
    }
    
    // Maybe this will prevent us from getting the spam increase to max hunger?
    K2_DestroyActor();
    
    
    // TODO: Call a function here to spawn emitter and sound effect.
    
}

void AMinorHungerPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (GEngine)
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Overlap Ending");
}
