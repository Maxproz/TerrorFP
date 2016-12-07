// Copyright @Maxpro 2016

#include "TerrorFP.h"
#include "InstructionalWidget.h"


UInstructionalWidget::UInstructionalWidget(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{

}

void UInstructionalWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    AssignAnimations();
    
    FLatentActionInfo ActionInfoPlayAnimation;
    ActionInfoPlayAnimation.CallbackTarget = this;
    ActionInfoPlayAnimation.ExecutionFunction = "PlayAnimationDelay";
    ActionInfoPlayAnimation.UUID = 2222;
    ActionInfoPlayAnimation.Linkage = 0;

    // Play the animation 5 seconds after being created
    UKismetSystemLibrary::Delay(this, 5.0, ActionInfoPlayAnimation);
        
}

void UInstructionalWidget::PlayAnimationDelay()
{
    PlayAnimation(WidgetAnim);
}

void UInstructionalWidget::AssignAnimations()
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

