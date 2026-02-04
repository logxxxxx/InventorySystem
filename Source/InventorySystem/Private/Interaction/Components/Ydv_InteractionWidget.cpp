


#include "Interaction/Components/Ydv_InteractionWidget.h"

#include "Item/Components/Ydv_ItemComponent.h"
#include "Widgets/Composite/Ydv_Composite.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"


UYdv_InteractionWidget::UYdv_InteractionWidget()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	SetVisibility(false);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);

}

void UYdv_InteractionWidget::ShowInteractionWidget()
{
	if (!IsValid(GetWidget())) return;
	
	SetVisibility(true);
	
	//Only done for the inventory item
	AssimilateInventoryWidget();
}

void UYdv_InteractionWidget::AssimilateInventoryWidget()
{
	if (!IsValid(GetOwner())) return;
	if (UYdv_ItemComponent* ItemComponent = GetOwner()->FindComponentByClass<UYdv_ItemComponent>(); IsValid(ItemComponent))
	{
		InteractionWidget = Cast<UYdv_CompositeBase>(GetWidget());
		if (!InteractionWidget.IsValid()) return;
		
		ItemComponent->GetItemManifest().AssimilateInventoryFragments(InteractionWidget.Get());
	}
}

void UYdv_InteractionWidget::HideInteractionWidget()
{
	SetVisibility(false);
	
	//Only for the inventory item
	if (InteractionWidget.IsValid())
	{
		Cast<UYdv_Composite>(InteractionWidget.Get())->Collapse();
	}
	
}

