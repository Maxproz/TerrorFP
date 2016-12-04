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
    
    /** Pawn mesh: 1st person view (arms; seen only by self) */
    UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
    class USkeletalMeshComponent* Mesh1P;
    
    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FirstPersonCameraComponent;
    
    // member variables
    /* Can re-enable these if I ever end up using the other type of timer.
    float ElapsedTimeMini;
    float ElapsedTimeFull;
    float Period;
    float TimerEnd;
    */

    // Flashlight is set to off at the start of the game.
    bool bIsFlashLightOn = false;
    
    // Variable to manage the flipflop in the DiscardItem action mapping
    bool bIsAOn = true;
    
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
    
    class ARifle* ThirdPersonRifle;
    
    class ARifle* FirstPersonRifle;
    
    // player starts holding a rifle for now.
    bool bIsHoldingRifle = true;
    
    int32 NumberOfWood = 0;
    
public:
	ATP_ThirdPersonCharacter();

    // TODO: Remove unnecessary UFUNCTION() https://answers.unrealengine.com/questions/129550/when-to-use-ufunction-macro.html
    // TODO: Filter out all these functions to their correct public/private/protected etc..
    
    UFUNCTION()
    int32 SetNumberOfWood(int32 Wood) { return NumberOfWood += Wood; }
    
    int32 GetNumberOfWood() { return NumberOfWood; }
    
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    class UFiringComponent* FiringComponent;
    
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<class ARifle> RifleBPThirdPerson;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<class ARifle> RifleBPFirstPerson;
    
    
    // TODO: Should this be public?
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hunger System")
    int32 PlayerHunger = 500;
    
    // TODO: This should probably be FText somehow
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest System")
    FString PlayerObjective = (TEXT("Collect Firewood"));
    
//    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System")
    static const FString PlayerSaveSlot;
    
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
    
    // TODO: Should this be public?
    // Widget to create and add to viewport on beginplay
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<class UObjectiveComplete> WidgetTemplateObjComplete;
    
    // TODO: Should this be public?
    class UObjectiveComplete* WidgetInstanceObjComplete;
    
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

    UFUNCTION()
    void DiscardItem();
    
    // Setters for the inventory slots
    void SetSlotOneItem(int32 Item) { SlotOneItem = Item; }
    void SetSlotTwoItem(int32 Item) { SlotTwoItem = Item; }
    void SetSlotThreeItem(int32 Item) { SlotThreeItem = Item; }
    void SetSlotFourItem(int32 Item) { SlotFourItem = Item; }
    void SetSlotFiveItem(int32 Item) { SlotFiveItem = Item; }
    
    
    // Cast it to an Image we can use
    // TODO: What protection should this have.
    // TODO: Try refactoring all these buttons into the SurvivalHUDWidget
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UButton* SlotOneButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidget* ItemButtonOne;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UButton* SlotTwoButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidget* ItemButtonTwo;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UButton* SlotThreeButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidget* ItemButtonThree;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UButton* SlotFourButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidget* ItemButtonFour;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UButton* SlotFiveButton;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidget* ItemButtonFive;
    
    UFUNCTION()
    void SlotOneButtonClicked();
    
    UFUNCTION()
    void SlotTwoButtonClicked();
    
    UFUNCTION()
    void SlotThreeButtonClicked();
    
    UFUNCTION()
    void SlotFourButtonClicked();
    
    UFUNCTION()
    void SlotFiveButtonClicked();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector PickupOffset = (FVector(100.0f, 0.0f, 60.0f));
    
    // Slot One Button Style
    FButtonStyle ButtonStyle;
    
protected:
    // TODO: Should these be private? Can they be private?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battery System")
    int32 PlayerBattery = 50;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint System")
    bool bIsSprintOn = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint System")
    int32 PlayerStamina = 100;
    
    // Inventory discard
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory System")
    bool bIsDiscardActive = false;
    
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

