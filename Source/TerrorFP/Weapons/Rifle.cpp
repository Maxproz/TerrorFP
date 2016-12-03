// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "Animation/AnimInstance.h"
#include "../TerrorFPProjectile.h"
#include "Rifle.h"


// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a gun mesh component
    FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
    FP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
    FP_Gun->bCastDynamicShadow = false;
    FP_Gun->CastShadow = false;
    // FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
    FP_Gun->SetupAttachment(RootComponent);
    
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("/Game/FirstPerson/Models/m4a1"));
    if (Mesh.Succeeded())
    {
        FP_Gun->SetSkeletalMesh(Mesh.Object);
        
        // To change the mesh location in case I need to later.
        //Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
        //Mesh->SetWorldScale3D(FVector(0.8f));
    }
    
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Game/FirstPerson/Models/m4a1Mat"));
    if (Material.Succeeded())
        FP_Gun->SetMaterial(0, Material.Object);
    
    
    FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    FP_MuzzleLocation->SetupAttachment(FP_Gun);
    FP_MuzzleLocation->SetRelativeLocation(FVector(0.45f, 60.32f, 11.01f));
    FP_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
   
    
}

// Called every frame
void ARifle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// TODO: this method currently never gets called. Remove once more comfortable with the code.
void ARifle::OnFire()
{
    // try and fire a projectile
    if (ProjectileClass != NULL)
    {
        UWorld* const World = GetWorld();
        if (World != NULL)
        {

            const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
            // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
            const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();
            
            // TODO: Research what these spawn params do.
            //Set Spawn Collision Handling Override
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
            
            // spawn the projectile at the muzzle
            World->SpawnActor<ATerrorFPProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
            
        }
    }
    
    
    // TODO: Clean up this code later.
    // try and play the sound if specified
    if (FireSound != NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
    
    // try and play a firing animation if specified
    if (FireAnimation != NULL)
    {
        // Get the animation object for the arms mesh
        if (AnimInstance != NULL)
        {
            AnimInstance->Montage_Play(FireAnimation, 1.f);
        }
    }
    
    
    // TODO: Decide if I still want to use this system or delete it.
//    FHitResult* HitResult = new FHitResult();
//    FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
//    FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
//    FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
//    FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
//    
//    if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
//    {
//        DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);
//        
//        ATarget* TestTarget = Cast<ATarget>(HitResult->Actor.Get());
//        
//        if (TestTarget != nullptr && !TestTarget->IsPendingKill())
//        {
//            TestTarget->DamageTarget(50.f);
//        }
//    }
}
