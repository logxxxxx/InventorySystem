#include "InventoryManagement/FastArray/Ydv_FastArray.h"

TArray<FYdv_InventoryItemEntry> FYdv_InventoryFastArray::GetAllItems()
{
}

void FYdv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FYdv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

void FYdv_InventoryFastArray::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
}

UYdv_InventoryItem* FYdv_InventoryFastArray::AddEntry(UYdv_InventoryItem* NewItem)
{
}

UYdv_InventoryItem* FYdv_InventoryFastArray::AddEntry(UYdv_ItemComponent* NewItemComponent)
{
}

void FYdv_InventoryFastArray::RemoveEntry(UYdv_InventoryItem* ItemToRemove)
{
}
