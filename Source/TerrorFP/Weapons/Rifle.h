// Copyright @Maxpro 2016

#pragma once

#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class TERRORFP_API ARifle : public AActor
{
	GENERATED_BODY()
	
private:
    /** Gun mesh: 1st person view (seen only by self) */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USkeletalMeshComponent* FP_Gun;
    
    /** Location on gun mesh where projectiles should spawn. */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USceneComponent* FP_MuzzleLocation;
    
public:	
	// Sets default values for this actor's properties
	ARifle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    /** Projectile class to spawn */
    UPROPERTY(EditAnywhere, Category=Projectile)
    TSubclassOf<class ATerrorFPProjectile> ProjectileClass;
	
    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class USoundBase* FireSound;
    
    /** AnimMontage to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimMontage* FireAnimation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimInstance* AnimInstance;

    /** Fires a projectile. */
    void OnFire();
    
};
