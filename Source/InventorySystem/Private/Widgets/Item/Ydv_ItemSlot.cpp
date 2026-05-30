


#include "Widgets/Item/Ydv_ItemSlot.h"

#include "Components/SizeBox.h"
#include "Item/Ydv_InventoryItem.h"

void UYdv_ItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UYdv_ItemSlot::SetBoxSize(const FVector2D& NewSize) const
{
	if (IsValid(SizeBox))
	{
		SizeBox->SetWidthOverride(NewSize.X);
		SizeBox->SetHeightOverride(NewSize.Y);
	}
}

void UYdv_ItemSlot::AddItemToSlot(UYdv_InventoryItem* ItemToAdd)
{
	if (!IsValid(ItemToAdd)) return;
	ItemToAdd->GetItemManifest().AssimilateInventoryFragments(this);
	InventoryItem = ItemToAdd;
	OnItemAddedToSlot(ItemToAdd);
}

void UYdv_ItemSlot::AddItemToSlot(UYdv_InventoryItem* ItemToAdd, const int32& InStackCount)
{
	if (!IsValid(ItemToAdd)) return;
	ItemToAdd->GetItemManifest().AssimilateInventoryFragments(this);
	InventoryItem = ItemToAdd;
	UpdateStackCount(StackCount + InStackCount);
	OnItemAddedToSlot(ItemToAdd);
}

void UYdv_ItemSlot::RemoveItemFromSlot(UYdv_InventoryItem* ItemToRemove)
{
	check(ItemToRemove == InventoryItem.Get());	
	Collapse();
	InventoryItem = nullptr;
	OnItemRemovedFromSlot(ItemToRemove);
}

void UYdv_ItemSlot::UpdateStackCount(int32 NewStackCount)
{
	if (!InventoryItem.IsValid()) return;
	StackCount = NewStackCount;
	OnStackCountUpdated(NewStackCount);
}
