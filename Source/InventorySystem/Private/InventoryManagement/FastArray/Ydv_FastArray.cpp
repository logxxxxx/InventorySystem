#include "InventoryManagement/FastArray/Ydv_FastArray.h"
#include "Item/Components/Ydv_ItemComponent.h"
#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "Item/Ydv_InventoryItem.h"

TArray<UYdv_InventoryItem*> FYdv_InventoryFastArray::GetAllItems()
{
	TArray<UYdv_InventoryItem*> Items;
	Items.Reserve(Entries.Num());
	for (const FYdv_InventoryItemEntry& Entry : Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		Items.Add(Entry.Item);
	}
	return Items;
}

void FYdv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UYdv_InventoryComponent* InventoryComp = Cast<UYdv_InventoryComponent>(OwnerComponent);
	if (!IsValid(InventoryComp)) return;
	for (int32 Index : RemovedIndices)
	{
		if (Entries.IsValidIndex(Index))
		{
			UYdv_InventoryItem* RemovedItem = Entries[Index].Item;
			if (IsValid(RemovedItem))
			{
				InventoryComp->OnItemRemovedFromTheInventory.Broadcast(RemovedItem);
			}
		}
	}
}

void FYdv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UYdv_InventoryComponent* Comp = Cast<UYdv_InventoryComponent>(OwnerComponent);
	if (!IsValid(Comp)) return;
	for (int32 Index : AddedIndices)
	{
		if (Entries.IsValidIndex(Index))
		{
			UYdv_InventoryItem* AddedItem = Entries[Index].Item;
			if (IsValid(AddedItem))
			{
				Comp->OnItemAddedToTheInventory.Broadcast(AddedItem);
			}
		}
	}
}

UYdv_InventoryItem* FYdv_InventoryFastArray::AddEntry(UYdv_InventoryItem* NewItem)
{
	check(OwnerComponent);
	AActor* OwnerActor = OwnerComponent->GetOwner();
	if (!IsValid(OwnerActor) || !IsValid(NewItem)) return nullptr;
	check(OwnerActor->HasAuthority());

	FYdv_InventoryItemEntry& Entry =  Entries.AddDefaulted_GetRef();
	Entry.Item = NewItem;
	MarkItemDirty(Entry);
	return NewItem;
}

UYdv_InventoryItem* FYdv_InventoryFastArray::AddEntry(UYdv_ItemComponent* NewItemComponent)
{
	check(OwnerComponent);
	AActor* OwnerActor = OwnerComponent->GetOwner();
	if (!IsValid(OwnerActor) || !IsValid(NewItemComponent)) return nullptr;
	check(OwnerActor->HasAuthority());
	UYdv_InventoryComponent* Comp = Cast<UYdv_InventoryComponent>(OwnerComponent);
	if (!IsValid(Comp)) return nullptr;
	
	UYdv_InventoryItem* NewItem = NewItemComponent->GetItemManifest().ManifestItem(OwnerActor);
	FYdv_InventoryItemEntry& Entry =  Entries.AddDefaulted_GetRef();
	Entry.Item = NewItem;
	
	Comp->AddRepSubObject(Entry.Item);
	MarkItemDirty(Entry);
	return NewItem;
}

void FYdv_InventoryFastArray::RemoveEntry(UYdv_InventoryItem* ItemToRemove)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		if (EntryIt->Item == ItemToRemove)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
			break;
		}
	}
}
