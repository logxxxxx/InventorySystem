


#include "Widgets/Interaction/Ydv_InteractionWidget.h"

#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "Item/Components/Ydv_ItemComponent.h"

void UYdv_InteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IsValid(GetOwningPlayer()))
	{
		if (UYdv_InventoryComponent* InventoryComponent = GetOwningPlayer()->FindComponentByClass<UYdv_InventoryComponent>(); IsValid(InventoryComponent))
		{
			InventoryComponent->OnPickupItemStackCountChange.AddDynamic(this, &ThisClass::OnStackCountChanged);
		}
	}
}

void UYdv_InteractionWidget::SetVisibility(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Collapsed || InVisibility == ESlateVisibility::Hidden)
	{
		Collapse();
	}
	else
	{
		Expand();
	}
}

void UYdv_InteractionWidget::OnStackCountChanged(UYdv_ItemComponent* ItemComponent, int32 NewStackCount)
{
	if (!IsValid(ItemComponent)) return;
	UpdateStackCount(NewStackCount);
}
