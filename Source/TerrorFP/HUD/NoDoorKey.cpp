// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "NoDoorKey.h"


UNoDoorKey::UNoDoorKey(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)

{
    static ConstructorHelpers::FObjectFinder<UTexture2D> KeyImg(TEXT("/Game/SurvivalHorrorGame/KeyInvItem"));
    KeyImageTexture = KeyImg.Object;
}

void UNoDoorKey::NativeConstruct()
{
    Super::NativeConstruct();
    
    AssignAnimations();
    PlayAnimation(WidgetAnim);
}

FSlateBrush UNoDoorKey::GetKeyPopupImage() const
{
    FSlateBrush KeyImgBrush;
    
    if (GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr)
    {
        return FSlateBrush();
    }
    
    ATP_ThirdPersonCharacter* Char = Cast<ATP_ThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    if (Char == nullptr)
    {
        return FSlateBrush();
    }
    
    KeyImgBrush.SetResourceObject(KeyImageTexture);
    return KeyImgBrush;
}

void UNoDoorKey::AssignAnimations()
{
    UProperty* prop = GetClass()->PropertyLink;
    
    // Run through all properties of this class to find any widget animations
    while( prop != nullptr  )
    {
        // Only interested in object properties
        if( prop->GetClass() == UObjectProperty::StaticClass() )
        {
            UObjectProperty* objectProp = Cast<UObjectProperty>(prop);
            
            // Only want the properties that are widget animations
            if( objectProp->PropertyClass == UWidgetAnimation::StaticClass() )
            {
                UObject* object = objectProp->GetObjectPropertyValue_InContainer( this );
                
                UWidgetAnimation* widgetAnim = Cast<UWidgetAnimation>(object);
                
                if( widgetAnim != nullptr )
                {
                    // TODO: Filter this functionality out into a TArray or struct like it says below.
                    // The current setup only works if there is one animation.
                    // DO SOMETHING TO STORE OFF THE ANIM PTR HERE!
                    WidgetAnim = widgetAnim;
                    // E.g. add to a TArray of some struct that holds info for each anim
                }
            }
        }
        
        prop = prop->PropertyLinkNext;
    }
}