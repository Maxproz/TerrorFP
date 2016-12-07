// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../HUD/InstructionalWidget.h"
#include "TerrorFPLevelScriptActor.h"


void ATerrorFPLevelScriptActor::BeginPlay()
{
    APlayerController* Player = GetWorld()->GetFirstPlayerController();
    if (!Player)
    { UE_LOG(LogTemp, Warning, TEXT("Not able to find player in level script actor")) return; }
    
    // Variables for control after coming in this level from the main menu.
    Player->bShowMouseCursor = 0;
    FInputModeGameOnly GameOnly;
    Player->SetInputMode(GameOnly);
    
    // Popup Widget for beginning game instructions
    InstructionWidget = CreateWidget<UInstructionalWidget>(Player, WidgetInstructionalTemplate);
    if (!InstructionWidget)
    { UE_LOG(LogTemp, Warning, TEXT("Something went wrong when creating Instructional Widget")) return; }
    
    InstructionWidget->AddToViewport();
    
}