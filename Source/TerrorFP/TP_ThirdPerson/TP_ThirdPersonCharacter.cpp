// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TerrorFP.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "../Items/WoodInvPickup.h"
#include "../Items/KeyPickup.h"
#include "../Weapons/Rifle.h"
#include "../Components/FiringComponent.h"
#include "../HUD/ObjectiveComplete.h"
#include "GameFramework/InputSettings.h"
#include "../HUD/NoDoorKey.h"
#include "../StaticConstantNames.h"
#include "../HUD/InstructionalWidget.h"
#include "../Game/TerrorFPLevelScriptActor.h"
#include "TP_ThirdPersonCharacter.h"


//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

const int32 PlayerHungerDecay = 5;
const int32 PlayerCountdownToNextHungerTick = 1;
static const FString SprintScrollingText(TEXT("Player Sprint: "));
static const FString HungerScrollingMessage(TEXT("Player Hunger: "));
const FString ATP_ThirdPersonCharacter::PlayerSaveSlot(TEXT("SurvivalSaveGame"));
const int32 DropOneWood = -1;


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
    
    // FIRST PERSON STUFF
    // Create a CameraComponent
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
    // Can't rely on this? reference https://www.udemy.com/unrealcourse/learn/v4/t/lecture/6090586
    // Changing this to true because it fixed the "cant move mouse cursor when stationary bug"
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
    
    
    
    // Create a mesh component that will be used when being viewed from a
    // - '1st person' view (when controlling this pawn)
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetupAttachment(FirstPersonCameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
    Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
    
    
    // Setup the tint color defaults to make the buttons see through
    ButtonStyle.Normal.TintColor = FLinearColor(1.0, 1.0, 1.0, 0.0);
    ButtonStyle.Pressed.TintColor = FLinearColor(1.0, 1.0, 1.0, 0.0);
    ButtonStyle.Hovered.TintColor = FLinearColor(1.0, 1.0, 1.0, 0.0);

    
    // TODO: remove this here or not? --- if (bIsHoldingRifle = true)
    FiringComponent = CreateDefaultSubobject<UFiringComponent>(TEXT("FiringComponent"));

    // TODO: Learn more about Movement/Rotation https://www.udemy.com/unrealcourse/learn/v4/t/lecture/5915890
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Make use this later in-order to not auto select the BP class?
    //YourCustomWidgetUIClass = LoadClass<YourCustomWidget>(..., TEXT(path_to_your_widget_in_content_browser), ...);
    
    WidgetInstanceObjComplete = CreateWidget<UObjectiveComplete>(GetWorld(), WidgetTemplateObjComplete);
    WidgetInstanceObjComplete->SetIsEnabled(false);
    
    // Create the widget that shows the player missing a key and hide it for now.
    WidgetInstanceNoDoorKey = CreateWidget<UNoDoorKey>(GetWorld(), WidgetTemplateNoDoorKey);
    WidgetInstanceNoDoorKey->SetIsEnabled(false);
    
    
//    // Starting Notification Widget
//    InstructionWidget = CreateWidget<UInstructionalWidget>(GetWorld(), WidgetTemplateInstWidget);
    

    

    
    
    // TODO: Do I need to disable the widget after it plays once to allow it to play again next time?
//    if (WidgetInstanceObjComplete->GetIsEnabled())
//    {
//        
//    }
    
    // Get the starting objective at begin play so the HUD can use it.
    
    WidgetInstance = CreateWidget<USurvivalHUDWidget>(GetWorld(), WidgetTemplate);
    if (WidgetInstance)
    {
        WidgetInstance->AddToViewport();
        
        // Old code ends here
        
        // TODO: Test this code to see if it works.
        ItemButtonOne = WidgetInstance->GetWidgetFromName("InvButtonOne");
        ItemButtonTwo = WidgetInstance->GetWidgetFromName("InvButtonTwo");
        ItemButtonThree = WidgetInstance->GetWidgetFromName("InvButtonThree");
        ItemButtonFour = WidgetInstance->GetWidgetFromName("InvButtonFour");
        ItemButtonFive = WidgetInstance->GetWidgetFromName("InvButtonFive");
        
        // Cast it to an Image we can use
        if (ItemButtonOne)
            SlotOneButton = Cast<UButton>(ItemButtonOne);
        
        if (ItemButtonOne)
            SlotTwoButton = Cast<UButton>(ItemButtonTwo);
        
        if (ItemButtonThree)
            SlotThreeButton = Cast<UButton>(ItemButtonThree);
        
        if (ItemButtonFour)
            SlotFourButton = Cast<UButton>(ItemButtonFour);
        
        if (ItemButtonFive)
            SlotFiveButton = Cast<UButton>(ItemButtonFive);
        
        if (SlotOneButton)
        {
            // Setup the colors
            SlotOneButton->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
            SlotOneButton->SetStyle(ButtonStyle);
            // Add the function binding.
            SlotOneButton->OnClicked.AddDynamic(this,&ATP_ThirdPersonCharacter::SlotOneButtonClicked);
        }
        
        if (SlotTwoButton)
        {
            SlotTwoButton->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
            SlotTwoButton->SetStyle(ButtonStyle);
            SlotTwoButton->OnClicked.AddDynamic(this,&ATP_ThirdPersonCharacter::SlotTwoButtonClicked);
        }
        
        if (SlotThreeButton)
        {
            SlotThreeButton->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
            SlotThreeButton->SetStyle(ButtonStyle);
            SlotThreeButton->OnClicked.AddDynamic(this,&ATP_ThirdPersonCharacter::SlotThreeButtonClicked);
        }
        
        if (SlotFourButton)
        {
            SlotFourButton->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
            SlotFourButton->SetStyle(ButtonStyle);
            SlotFourButton->OnClicked.AddDynamic(this,&ATP_ThirdPersonCharacter::SlotFourButtonClicked);
        }
        
        if (SlotFiveButton)
        {
            SlotFiveButton->SetColorAndOpacity(FLinearColor(1.0,1.0,1.0,0.0));
            SlotFiveButton->SetStyle(ButtonStyle);
            SlotFiveButton->OnClicked.AddDynamic(this,&ATP_ThirdPersonCharacter::SlotFiveButtonClicked);
        }
    }

    // TODO: Think about refactoring this rifle code into a conditional for pickup.
    if (RifleBPThirdPerson == nullptr) { return; }
    ThirdPersonRifle = GetWorld()->SpawnActor<ARifle>(RifleBPThirdPerson);
    
    if (RifleBPFirstPerson == nullptr) { return; }
    FirstPersonRifle = GetWorld()->SpawnActor<ARifle>(RifleBPFirstPerson);
    
    // Attach gun mesh component to Skeleton,
    // - doing it here because the skeleton is not yet created in the constructor
    FName fnWeaponSocket = TEXT("MFGrip");
    FName FirstPersonRifleSocket = TEXT("GripPoint");
    
    FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
    ThirdPersonRifle->AttachToComponent(GetMesh(), rules, fnWeaponSocket);
    FirstPersonRifle->AttachToComponent(Mesh1P, rules, FirstPersonRifleSocket);
    
    FiringComponent->SetupAttachment(FirstPersonCameraComponent);
    FiringComponent->SetRelativeLocation(FVector(159.5599f, -1.75f, -16.0f));
    FiringComponent->AnimInstance = Mesh1P->GetAnimInstance();

    
    ThirdPersonRifle->AnimInstance = GetMesh()->GetAnimInstance();
    // FirstPersonRifle->AnimInstance = Mesh1P->GetAnimInstance();

    // Fire function bind here so we know for a fact it gets bound at the right time.
    InputComponent->BindAction("Fire", IE_Pressed, FiringComponent, &UFiringComponent::OnFire);
    
    
    
//    // Instruction Widget Stuff
//    if (InstructionWidget)
//    {
//        InstructionWidget->AddToViewport();
//    }
    
    

    
}

// Called every frame
void ATP_ThirdPersonCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    // Update the camera on Tick
    
    FRotator PawnRotation = GetControlRotation();
    float PawnRotationPitch = PawnRotation.Pitch;
    FRotator NewRotation = FRotator(PawnRotationPitch, 0.0, 0.0);
    // TODO: Is this even doing anything? Should it be FirstPersonCamera or CameraBoom
    CameraBoom->SetRelativeRotation(NewRotation);
    
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
//    if (bHasClicked == true)
//    {
//        InstructionWidget->RemoveFromParent();
//    }
//    
//}
//
//void ATP_ThirdPersonCharacter::PlayerHasClickedStartingNotification()
//{
//    bHasClicked = true;
//}

// TODO: This should probably be in the SurvivalHUDWidget.cpp
// TODO: Would it be better to spawn from a blueprint template instead of static class?
void ATP_ThirdPersonCharacter::SlotOneButtonClicked()
{
    if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Slot One Button Clicked!");
    
    // Item to be used in our switch statement
    int32 Item = GetSlotOneItem();
    
    // Get the player Transform so we can use its rotation.
    FTransform PlayerContTransformInfo = UGameplayStatics::GetPlayerController(this, 0)->GetActorTransform();

    // The Transform that we will spawn the item at.
    FTransform ItemSpawnTransform;

    // Get the data for the spawning item
    FVector RotatedVector = PlayerContTransformInfo.GetRotation().RotateVector(PickupOffset);
    FVector ItemSpawnLocation = GetActorLocation() + RotatedVector;
    
    ItemSpawnTransform.SetRotation(PlayerContTransformInfo.GetRotation());
    ItemSpawnTransform.SetLocation(ItemSpawnLocation);
    ItemSpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            // do nothing
            break;
        }
        case StaticConstantNames::WoodID:
        {
            GetWorld()->SpawnActor(AWoodInvPickup::StaticClass(), &ItemSpawnTransform);
            SetNumberOfWood(DropOneWood);
            SetSlotOneItem(StaticConstantNames::EmptyID);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            GetWorld()->SpawnActor(AKeyPickup::StaticClass(), &ItemSpawnTransform);
            SetPlayerHasDoubleDoorKey(false);
            SetSlotOneItem(StaticConstantNames::EmptyID);
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Not able to Spawn Actor Item1");
        }
    }
}

void ATP_ThirdPersonCharacter::SlotTwoButtonClicked()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Slot Two Button Clicked!");
    
    // Item to be used in our switch statement
    int32 Item = GetSlotTwoItem();
    
    // Get the player Transform so we can use its rotation.
    FTransform PlayerContTransformInfo = UGameplayStatics::GetPlayerController(this, 0)->GetActorTransform();
    
    // The Transform that we will spawn the item at.
    FTransform ItemSpawnTransform;
    
    // Get the data for the spawning item
    FVector RotatedVector = PlayerContTransformInfo.GetRotation().RotateVector(PickupOffset);
    FVector ItemSpawnLocation = GetActorLocation() + RotatedVector;
    
    ItemSpawnTransform.SetRotation(PlayerContTransformInfo.GetRotation());
    ItemSpawnTransform.SetLocation(ItemSpawnLocation);
    ItemSpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            // do nothing
            break;
        }
        case StaticConstantNames::WoodID:
        {
            GetWorld()->SpawnActor(AWoodInvPickup::StaticClass(), &ItemSpawnTransform);
            SetNumberOfWood(DropOneWood);
            SetSlotTwoItem(StaticConstantNames::EmptyID);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            GetWorld()->SpawnActor(AKeyPickup::StaticClass(), &ItemSpawnTransform);
            SetPlayerHasDoubleDoorKey(false);
            SetSlotTwoItem(StaticConstantNames::EmptyID);
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Not able to Spawn Actor Item2");
        }
    }
}

void ATP_ThirdPersonCharacter::SlotThreeButtonClicked()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Slot Three Button Clicked!");
    
    // Item to be used in our switch statement
    int32 Item = GetSlotThreeItem();
    
    // Get the player Transform so we can use its rotation.
    FTransform PlayerContTransformInfo = UGameplayStatics::GetPlayerController(this, 0)->GetActorTransform();
    
    // The Transform that we will spawn the item at.
    FTransform ItemSpawnTransform;
    
    // Get the data for the spawning item
    FVector RotatedVector = PlayerContTransformInfo.GetRotation().RotateVector(PickupOffset);
    FVector ItemSpawnLocation = GetActorLocation() + RotatedVector;
    
    ItemSpawnTransform.SetRotation(PlayerContTransformInfo.GetRotation());
    ItemSpawnTransform.SetLocation(ItemSpawnLocation);
    ItemSpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            // do nothing
            break;
        }
        case StaticConstantNames::WoodID:
        {
            GetWorld()->SpawnActor(AWoodInvPickup::StaticClass(), &ItemSpawnTransform);
            SetNumberOfWood(DropOneWood);
            SetSlotThreeItem(StaticConstantNames::EmptyID);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            GetWorld()->SpawnActor(AKeyPickup::StaticClass(), &ItemSpawnTransform);
            SetPlayerHasDoubleDoorKey(false);
            SetSlotThreeItem(StaticConstantNames::EmptyID);
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Not able to Spawn Actor Item3");
        }
    }
}

void ATP_ThirdPersonCharacter::SlotFourButtonClicked()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Slot Four Button Clicked!");
    
    // Item to be used in our switch statement
    int32 Item = GetSlotFourItem();
    
    // Get the player Transform so we can use its rotation.
    FTransform PlayerContTransformInfo = UGameplayStatics::GetPlayerController(this, 0)->GetActorTransform();
    
    // The Transform that we will spawn the item at.
    FTransform ItemSpawnTransform;
    
    // Get the data for the spawning item
    FVector RotatedVector = PlayerContTransformInfo.GetRotation().RotateVector(PickupOffset);
    FVector ItemSpawnLocation = GetActorLocation() + RotatedVector;
    
    ItemSpawnTransform.SetRotation(PlayerContTransformInfo.GetRotation());
    ItemSpawnTransform.SetLocation(ItemSpawnLocation);
    ItemSpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            // do nothing
            break;
        }
        case StaticConstantNames::WoodID:
        {
            GetWorld()->SpawnActor(AWoodInvPickup::StaticClass(), &ItemSpawnTransform);
            SetNumberOfWood(DropOneWood);
            SetSlotFourItem(StaticConstantNames::EmptyID);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            GetWorld()->SpawnActor(AKeyPickup::StaticClass(), &ItemSpawnTransform);
            SetPlayerHasDoubleDoorKey(false);
            SetSlotFourItem(StaticConstantNames::EmptyID);
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Not able to Spawn Actor Item4");
        }
    }
}

void ATP_ThirdPersonCharacter::SlotFiveButtonClicked()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Slot Five Button Clicked!");
    
    // Item to be used in our switch statement
    int32 Item = GetSlotFiveItem();
    
    // Get the player Transform so we can use its rotation.
    FTransform PlayerContTransformInfo = UGameplayStatics::GetPlayerController(this, 0)->GetActorTransform();
    
    // The Transform that we will spawn the item at.
    FTransform ItemSpawnTransform;
    
    // Get the data for the spawning item
    FVector RotatedVector = PlayerContTransformInfo.GetRotation().RotateVector(PickupOffset);
    FVector ItemSpawnLocation = GetActorLocation() + RotatedVector;
    
    ItemSpawnTransform.SetRotation(PlayerContTransformInfo.GetRotation());
    ItemSpawnTransform.SetLocation(ItemSpawnLocation);
    ItemSpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
    
    switch (Item)
    {
        case StaticConstantNames::EmptyID:
        {
            // do nothing
            break;
        }
        case StaticConstantNames::WoodID:
        {
            GetWorld()->SpawnActor(AWoodInvPickup::StaticClass(), &ItemSpawnTransform);
            SetNumberOfWood(DropOneWood);
            SetSlotFiveItem(StaticConstantNames::EmptyID);
            break;
        }
        case StaticConstantNames::KeyID:
        {
            GetWorld()->SpawnActor(AKeyPickup::StaticClass(), &ItemSpawnTransform);
            SetPlayerHasDoubleDoorKey(false);
            SetSlotFiveItem(StaticConstantNames::EmptyID);
            break;
        }
        default:
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Not able to Spawn Actor Item5");
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
    
    // Inventory Discard
    PlayerInputComponent->BindAction("ToggleDiscard", IE_Pressed, this, &ATP_ThirdPersonCharacter::DiscardItem);
}

void ATP_ThirdPersonCharacter::DiscardItem()
{
    // A is always going to be "On" the first time this function is called
    if (bIsAOn) // Run A
    {
        // Turn Discard active on.
        bIsDiscardActive = true;
        
        APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        
        if (PlayerController)
        {
            FInputModeGameAndUI GameAndUI;
            PlayerController->SetInputMode(GameAndUI);
            // Enable the mouse cursor + other settings during When Discard is enabled.
            PlayerController->bShowMouseCursor = 1;
            
            // TODO: Figure out if these are even needed or if the FInputMode setters are enough.
            PlayerController->bEnableClickEvents = 1;
            PlayerController->bEnableMouseOverEvents = 1;

            
            // TODO: Remove debug code
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Discarding");
        }
        
        // Make it so B runs next
        bIsAOn = false;
    }
    else // Run B
    {
        // Turn Discard active off
        bIsDiscardActive = false;
        
        APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
        
        if (PlayerController)
        {
            FInputModeGameOnly GameOnly;
            PlayerController->SetInputMode(GameOnly);
            
            // Enable the mouse cursor during When Discard is enabled.
            PlayerController->bShowMouseCursor = 0;

            // TODO: Remove debug code
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Not Discarding");
        }
        
        // Make it so A runs next
        bIsAOn = true;
    }
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


