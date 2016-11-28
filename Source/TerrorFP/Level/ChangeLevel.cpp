// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "ChangeLevel.h"


// Sets default values
AChangeLevel::AChangeLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
    SetRootComponent(StaticMeshComp);
    
    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleSystem"));
    ParticleSystem->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
    
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
    BoxCollider->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

    BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AChangeLevel::OnOverlapBegin);
    BoxCollider->bGenerateOverlapEvents = true;
    BoxCollider->SetRelativeLocation(FVector(0,0,192));
    BoxCollider->SetRelativeScale3D(FVector(7.2, 8.0, 6.9));
    
}

// Called when the game starts or when spawned
void AChangeLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChangeLevel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    
}

void AChangeLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UGameplayStatics::OpenLevel(GetWorld(), "LevelOne");
}
