// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "BatteryPickup.h"


// Sets default values
ABatteryPickup::ABatteryPickup()
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
    static ConstructorHelpers::FObjectFinder<UMaterial> CubeVisualAssetMaterial(TEXT("/Game/Textures/Battery/BatterPickup_Diffuse_Mat"));
    if (CubeVisualAsset.Succeeded())
    {
        Cube->SetMaterial(0, CubeVisualAssetMaterial.Object);
    }
    
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
    BoxCollision->SetRelativeScale3D(FVector(2.0, 2.0, 2.0));
    BoxCollision->AttachToComponent(Cube, FAttachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform));
    BoxCollision->bGenerateOverlapEvents = true;
    
    
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABatteryPickup::OnOverlapBegin);
    BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABatteryPickup::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABatteryPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABatteryPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABatteryPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Battery Overlap Starting");
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    
    Char->PickupBattery(BatteryPickupAmount);
    
    // If Battery amount is greater than 100 (max) set it to 100
    if (Char->GetPlayerBattery() > 100)
    {
        Char->SetMaxBattery();
        
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                "Player Battery MAX reached! Set to: " + FString::FromInt(Char->GetPlayerBattery()));
    }
    else
    {
        // Do nothing.. working just fine.
    }

    // Destroy the actor after first execution to prevent spam filling.
    K2_DestroyActor();
    
    
    // TODO: Call a function here to spawn emitter and sound effect.
    
}

void ABatteryPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // Not using for right now.
    
//    if (GEngine)
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Overlap Ending");
}
