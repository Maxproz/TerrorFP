// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "ObjectiveChange.h"


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
