// Copyright @Maxpro 2016

#pragma once

#include "Components/SceneComponent.h"
#include "FiringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRORFP_API UFiringComponent : public USceneComponent
{
	GENERATED_BODY()
    
private:
    class ATerrorFPProjectile* Projectile;

public:	
	// Sets default values for this component's properties
	UFiringComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    void OnFire();
    
    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class USoundBase* FireSound;
    
    /** AnimMontage to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimMontage* FireAnimation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimInstance* AnimInstance;
    
protected:
    /** Projectile class to spawn */
    UPROPERTY(EditAnywhere, Category=Projectile)
    TSubclassOf<class ATerrorFPProjectile> ProjectileClass;
    
    
};
