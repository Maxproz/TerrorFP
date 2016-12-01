// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "../HUD/SurvivalHUDWidget.h"
#include "TP_ThirdPersonCharacter.generated.h"

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

private:
    
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = "true"))
    class USpotLightComponent* SpotLight;
    
    // member variables
    /* Can re-enable these if I ever end up using the other type of timer.
    float ElapsedTimeMini;
    float ElapsedTimeFull;
    float Period;
    float TimerEnd;
    */

    // Flashlight is set to off at the start of the game.
    bool bIsFlashLightOn = false;

    
    // Inventory Slots for the Items.
    // TODO: Should these be private?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    int32 SlotOneItem;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    int32 SlotTwoItem;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    int32 SlotThreeItem;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    int32 SlotFourItem;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    int32 SlotFiveItem;
    
public:
	ATP_ThirdPersonCharacter();

    // TODO: Remove unnecessary UFUNCTION() https://answers.unrealengine.com/questions/129550/when-to-use-ufunction-macro.html
    // TODO: Filter out all these functions to their correct public/private/protected etc..
    
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // TODO: Should this be public?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hunger System")
    int32 PlayerHunger = 100;
    
    // TODO: This should probably be FText somehow
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest System")
    FString PlayerObjective = "Start Mission";
    
    // TODO: Rename this function to what it actually does.
    UFUNCTION()
    void SetPlayerHunger();
    
    UFUNCTION()
    void MinorHungerPickup(int32 Hunger);
    
    UFUNCTION()
    int32 GetPlayerHunger() const { return PlayerHunger; }
    
    // TODO: Should this be public?
    // Widget to create and add to viewport on beginplay
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<USurvivalHUDWidget> WidgetTemplate;
    
    // TODO: Should this be public? 
    USurvivalHUDWidget* WidgetInstance;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void Sprinting();
    
    UFUNCTION()
    void StopSprinting();
    
    UFUNCTION()
    void AdjustSprintAmount();
    
    UFUNCTION()
    void NotSprintingRecovery();
    
    UFUNCTION()
    void FlashLight();
    
    UFUNCTION()
    void AdjustBatteryAmount();
    
    UFUNCTION(BlueprintCallable, Category = "Battery System")
    void PickupBattery(int32 BatteryAmount) { PlayerBattery = PlayerBattery + BatteryAmount; }
    
    UFUNCTION()
    int32 GetPlayerBattery() const { return PlayerBattery; }
    
    UFUNCTION()
    void SetMaxBattery() { PlayerBattery = 100; }
    
    // Setters for the inventory slots
    void SetSlotOneItem(int32 Item) { SlotOneItem = Item; }
    void SetSlotTwoItem(int32 Item) { SlotTwoItem = Item; }
    void SetSlotThreeItem(int32 Item) { SlotThreeItem = Item; }
    void SetSlotFourItem(int32 Item) { SlotFourItem = Item; }
    void SetSlotFiveItem(int32 Item) { SlotFiveItem = Item; }
    
protected:
    // TODO: Should these be private? Can they be private?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battery System")
    int32 PlayerBattery = 50;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint System")
    bool bIsSprintOn = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint System")
    int32 PlayerStamina = 100;
    
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    /** Returns SpotLight subobject **/
    FORCEINLINE class USpotLightComponent* GetSpotLight() const { return SpotLight; }
                                                                                  
    FORCEINLINE int32 GetSlotOneItem() const { return SlotOneItem; }
    FORCEINLINE int32 GetSlotTwoItem() const { return SlotTwoItem; }
    FORCEINLINE int32 GetSlotThreeItem() const { return SlotThreeItem; }
    FORCEINLINE int32 GetSlotFourItem() const { return SlotFourItem; }
    FORCEINLINE int32 GetSlotFiveItem() const { return SlotFiveItem; }
};

