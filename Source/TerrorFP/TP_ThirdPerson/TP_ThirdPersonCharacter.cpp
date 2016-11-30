// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TerrorFP.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "TP_ThirdPersonCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

const int32 PlayerHungerDecay = 5;
const int32 PlayerCountdownToNextHungerTick = 1;
static const FString SprintScrollingText(TEXT("Player Sprint: "));
static const FString HungerScrollingMessage(TEXT("Player Hunger: "));

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
	
    // Set timer variables for hunger functionality
//    ElapsedTimeMini = 0.f;
//    ElapsedTimeFull = 0.f;
//    Period = 5.f;
//    TimerEnd = 5.f;
    
    // Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
    
    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetRelativeLocation(FVector(344, -9, 60));
    SpotLight->SetIntensity(200000.0);
    SpotLight->SetupAttachment(GetFollowCamera());
    SpotLight->SetVisibility(false);
    
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Make use this later in-order to not auto select the BP class?
    //YourCustomWidgetUIClass = LoadClass<YourCustomWidget>(..., TEXT(path_to_your_widget_in_content_browser), ...);
    
    WidgetInstance = CreateWidget<USurvivalHUDWidget>(GetWorld(), WidgetTemplate);
    
    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
    }
}

// Called every frame
void ATP_ThirdPersonCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    FLatentActionInfo LatentActionInfoHunger;
    LatentActionInfoHunger.CallbackTarget = this;
    LatentActionInfoHunger.ExecutionFunction = "SetPlayerHunger";
    LatentActionInfoHunger.UUID = 123;
    LatentActionInfoHunger.Linkage = 0;
    
    
    if (PlayerHunger > 1)
    {
        UKismetSystemLibrary::Delay(this, PlayerCountdownToNextHungerTick, LatentActionInfoHunger);
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("You died"));
            UGameplayStatics::SetGamePaused(this, true);
        }
    }
    
//    ElapsedTimeMini += DeltaTime;
//    ElapsedTimeFull += DeltaTime;

    
//    
//    if (PlayerHunger > 1)
//    {
//        if (ElapsedTimeMini >= Period)
//        {
//            SetPlayerHunger();
//            // We subtract the Period, instead of setting it to zero so it is more accurate
//            // example: if ElapsedTimeMini is 1.2, setting it to zero would make us lose 0.2 seconds
//            ElapsedTimeMini -= Period;
//        }
////        UKismetSystemLibrary::Delay(this, 5, LatentActionInfo);
//    }
//    else
//    {
//        if (GEngine)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("You died"));
//            UGameplayStatics::SetGamePaused(this, true);
//        }
//    }
//    
    // Don't need, timer is deactived by death
    /*
    if (ElapsedTimeFull >= TimerEnd)
    {
        //disable and reset variables
        SetActorTickEnabled(false);
        ElapsedTimeMini = 0.f;
        ElapsedTimeFull = 0.f;
    }
     */
    
    // Code for timer event to start in-case I need it later.
    /*
    //Timer event, let's say it's activated by a button push for sake of argument
    void MyClass::Event(){
        //enable tick on the actor
        SetActorTickEnabled(true);
     */
    
    // TODO: filter out the below two logics into functions
    
    // TODO: Sequence node said the above stuff runs first, then this stuff below.
    // Sprint stuff
    FLatentActionInfo LatentActionInfoSprintOn;
    LatentActionInfoSprintOn.CallbackTarget = this;
    LatentActionInfoSprintOn.ExecutionFunction = "AdjustSprintAmount";
    LatentActionInfoSprintOn.UUID = 1234;
    LatentActionInfoSprintOn.Linkage = 0;
    
    FLatentActionInfo LatentActionInfoSprintOff;
    LatentActionInfoSprintOff.CallbackTarget = this;
    LatentActionInfoSprintOff.ExecutionFunction = "NotSprintingRecovery";
    LatentActionInfoSprintOff.UUID = 1235;
    LatentActionInfoSprintOff.Linkage = 0;
    
    // Delayed function calls that monitor sprinting variables
    if (bIsSprintOn)
    {
        UKismetSystemLibrary::Delay(this, 0.2, LatentActionInfoSprintOn);
    }
    else
    {
        UKismetSystemLibrary::Delay(this, 0.2, LatentActionInfoSprintOff);
    }
    
    
    
    
    // TODO: Sequence node said the above stuff runs first and second, then this stuff third
    // Battery stuff
    
    FLatentActionInfo LatentActionInfoBatteryOn;
    LatentActionInfoBatteryOn.CallbackTarget = this;
    LatentActionInfoBatteryOn.ExecutionFunction = "AdjustBatteryAmount";
    LatentActionInfoBatteryOn.UUID = 1236;
    LatentActionInfoBatteryOn.Linkage = 0;
    
    if (bIsFlashLightOn)
    {
        if (PlayerBattery > 0)
        {
            UKismetSystemLibrary::Delay(this, 0.2, LatentActionInfoBatteryOn);
        }
        else
        {
            SpotLight->ToggleVisibility();
            bIsFlashLightOn = false;
            
            if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "FlashLight Battery Died!");
        }
    }
}

void ATP_ThirdPersonCharacter::AdjustBatteryAmount()
{
    PlayerBattery = PlayerBattery - 1;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                                     "Player Battery" + FString::FromInt(PlayerBattery));
    return;
}

void ATP_ThirdPersonCharacter::AdjustSprintAmount()
{
    if (PlayerStamina <= 0)
    {
        bIsSprintOn = false;
        GetCharacterMovement()->MaxWalkSpeed = 600;
        return;
    }
    else
    {
        PlayerStamina = PlayerStamina - 1;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
                                         SprintScrollingText + FString::FromInt(PlayerStamina));
        return;
    }
}

void ATP_ThirdPersonCharacter::NotSprintingRecovery()
{
    // Code to make sure stamina doesn't go above 100
    if (PlayerStamina < 100)
    {
        PlayerStamina = PlayerStamina + 1;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
                                         SprintScrollingText + FString::FromInt(PlayerStamina));
    }
    else
    {
        // We probably don't need to do anything here
    }
}

void ATP_ThirdPersonCharacter::SetPlayerHunger()
{
    PlayerHunger = PlayerHunger - PlayerHungerDecay;
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black,
                                         HungerScrollingMessage + FString::FromInt(PlayerHunger));
    }
    
}

void ATP_ThirdPersonCharacter::MinorHungerPickup(int32 Hunger)
{
    PlayerHunger = PlayerHunger + Hunger;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATP_ThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATP_ThirdPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATP_ThirdPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATP_ThirdPersonCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATP_ThirdPersonCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATP_ThirdPersonCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATP_ThirdPersonCharacter::OnResetVR);
    
    // Sprint Functionality
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATP_ThirdPersonCharacter::Sprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATP_ThirdPersonCharacter::StopSprinting);
    
    // FlashLight Functionality
    PlayerInputComponent->BindAction("FlashLight", IE_Pressed, this, &ATP_ThirdPersonCharacter::FlashLight);

}

void ATP_ThirdPersonCharacter::FlashLight()
{
    if (bIsFlashLightOn == true)
    {
        SpotLight->SetVisibility(false);
        bIsFlashLightOn = false;
    }
    else
    {
        if (PlayerBattery > 0)
        {
            SpotLight->SetVisibility(true);
            bIsFlashLightOn = true;
        }
    }
}

void ATP_ThirdPersonCharacter::Sprinting()
{
    if (PlayerStamina >= 1)
    {
        bIsSprintOn = true;
        // Default MaxWalkSpeed for TP_Template is 600, grant double bonus for sprint.
        GetCharacterMovement()->MaxWalkSpeed = 1200;
    }
}

void ATP_ThirdPersonCharacter::StopSprinting()
{
    bIsSprintOn = false;
    GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ATP_ThirdPersonCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATP_ThirdPersonCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATP_ThirdPersonCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATP_ThirdPersonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATP_ThirdPersonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATP_ThirdPersonCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATP_ThirdPersonCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


