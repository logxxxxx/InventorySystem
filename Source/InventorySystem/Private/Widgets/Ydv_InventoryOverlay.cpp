

#include "Widgets/Ydv_InventoryOverlay.h"
#include "Widgets/Item/Ydv_ItemInventory.h"


void UYdv_InventoryOverlay::ConstructItemInventory(int32 ItemSlots) const
{
	if (!IsValid(ItemInventory)) return;
	ItemInventory->ConstructItemSlots(ItemSlots);
}
