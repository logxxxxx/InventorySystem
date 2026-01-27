#include "Item/Manifest/Ydv_ItemManifest.h"

#include "Item/Ydv_InventoryItem.h"

UYdv_InventoryItem* FYdv_ItemManifest::ManifestItem(UObject* NewOuter) const
{
	UYdv_InventoryItem* NewItem = NewObject<UYdv_InventoryItem>(NewOuter);
	NewItem->SetItemManifest(*this);
	return NewItem;
}
