


#include "Interaction/Components/Ydv_InteractionWidgetComponent.h"
#include "Item/Components/Ydv_ItemComponent.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"
#include "Widgets/Interaction/Ydv_InteractionWidget.h"


UYdv_InteractionWidgetComponent::UYdv_InteractionWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetVisibility(false);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	SetDrawSize(FVector2D(200.f, 100.f));
}

void UYdv_InteractionWidgetComponent::ShowInteractionWidget(const AActor* Actor)
{
	if (!IsValid(GetWidget()) || !IsValid(Actor)) return;
	
	FVector WidgetLocation = FVector(Actor->GetActorLocation().X, Actor->GetActorLocation().Y, Actor->GetActorLocation().Z + 50.f);
	SetWorldLocation(WidgetLocation);
	
	SetVisibility(true);
	AssimilateInventoryWidget(Actor);
}

void UYdv_InteractionWidgetComponent::HideInteractionWidget()
{
	if (!IsValid(GetWidget())) return;
	if (!GetVisibleFlag()) return;
	SetInteractionWidgetVisibility(ESlateVisibility::Collapsed);
	SetVisibility(false);

}

void UYdv_InteractionWidgetComponent::AssimilateInventoryWidget(const AActor* Actor) const
{
	if (!IsValid(Actor)) return;
	if (UYdv_ItemComponent* ItemComponent = Actor->FindComponentByClass<UYdv_ItemComponent>(); IsValid(ItemComponent))
	{
		UYdv_CompositeBase* InteractionWidget = Cast<UYdv_CompositeBase>(GetWidget());
		if (!IsValid(InteractionWidget)) return;
		ItemComponent->GetItemManifest().AssimilateInventoryFragments(InteractionWidget);
	}
}

void UYdv_InteractionWidgetComponent::SetInteractionWidgetVisibility(ESlateVisibility InVisibility) const
{
	if (!IsValid(GetWidget())) return;
	UYdv_InteractionWidget* InteractionWidget = Cast<UYdv_InteractionWidget>(GetWidget());
	if (IsValid(InteractionWidget))
	{	
		InteractionWidget->SetVisibility(InVisibility);
	}
}

