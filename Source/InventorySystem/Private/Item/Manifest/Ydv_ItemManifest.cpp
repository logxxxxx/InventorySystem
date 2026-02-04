#include "Item/Manifest/Ydv_ItemManifest.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"
#include "Item/Ydv_InventoryItem.h"
#include "Item/Fragments/Ydv_ItemFragment.h"

UYdv_InventoryItem* FYdv_ItemManifest::ManifestItem(UObject* NewOuter) const
{
	UYdv_InventoryItem* NewItem = NewObject<UYdv_InventoryItem>(NewOuter);
	NewItem->SetItemManifest(*this);
	return NewItem;
}

void FYdv_ItemManifest::AssimilateInventoryFragments(UYdv_CompositeBase* Composite) const
{
	const auto& InventoryItemFragments = GetAllFragmentsOfType<FYdv_InventoryItemFragment>();
	for (const auto* Fragment : InventoryItemFragments)
	{
		Composite->ApplyFunction([Fragment](UYdv_CompositeBase* Widget)
		{
			Fragment->Assimilate(Widget);
		});
	}
}
