#include "Widgets/Item/Ydv_ItemInventory.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/Spacer.h"
#include "Interfaces/IHttpResponse.h"
#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "InventoryManagement/Utils/Ydv_InventoryStatics.h"
#include "Item/Ydv_InventoryItem.h"
#include "Item/Fragments/Ydv_ItemFragment.h"
#include "Widgets/Item/Ydv_ItemSlot.h"


void UYdv_ItemInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UYdv_InventoryComponent* InventoryComponent = UYdv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnItemAddedToTheInventory.AddDynamic(this, &ThisClass::OnItemAddedToInventory);
		InventoryComponent->OnInventoryItemStackCountChange.AddDynamic(this, &ThisClass::OnStackCountChange);
	}
}

void UYdv_ItemInventory::AddItemToInventorySlot(UYdv_InventoryItem* ItemToAdd)
{
	if (!IsValid(ItemToAdd)) return;
	for (UYdv_ItemSlot* ItemSlot : InventorySlots)
	{
		if (IsValid(ItemSlot->GetInventoryItem())) continue;
		ItemSlot->AddItemToSlot(ItemToAdd);
		break;
	}
}

void UYdv_ItemInventory::AddItemToInventorySlot(UYdv_InventoryItem* ItemToAdd, int32 StackCount)
{
	if (!IsValid(ItemToAdd)) return;
	for (UYdv_ItemSlot* ItemSlot : InventorySlots)
	{
		if (IsValid(ItemSlot->GetInventoryItem())) continue;
		ItemSlot->AddItemToSlot(ItemToAdd, StackCount);
		break;
	}
}

void UYdv_ItemInventory::OnItemAddedToInventory(UYdv_InventoryItem* ItemToAdd)
{
	if (!IsValid(ItemToAdd)) return;
	//Is item stackable ?
	if (ItemToAdd->GetItemManifest().GetFragmentOfType<FYdv_StackableFragment>()==nullptr)
	{
		AddItemToInventorySlot(ItemToAdd);
	}

}

void UYdv_ItemInventory::OnStackCountChange(UYdv_InventoryItem* Item, int32 InStackCount)
{
	if (!IsValid(Item)) return;
	if (Item->GetItemManifest().GetFragmentOfType<FYdv_StackableFragment>() ==nullptr) return;
	int16 StackCounter = 0;
	int32 MaxStackCount = Item->GetItemManifest().GetFragmentOfType<FYdv_StackableFragment>()->GetMaxStackSize();
	for (UYdv_ItemSlot* ItemSlot : InventorySlots)
	{
		if (ItemSlot->GetInventoryItem() != Item) continue;
		StackCounter = StackCounter + ItemSlot->GetStackCount();
		if (ItemSlot->GetStackCount() == MaxStackCount) continue;
		ItemSlot->UpdateStackCount(ItemSlot->GetStackCount() + InStackCount);
		return;
	}
	AddItemToInventorySlot(Item, InStackCount);
}

void UYdv_ItemInventory::ConstructItemSlots(const int32& TotalSlots)
{
	if (!IsValid(InventorySlotClass) || !IsValid(InventoryHorizontalBox)) return;
	InventorySlots.Reserve(TotalSlots);
	
	FVector2D BoxSize;
	BoxSize.X = (TotalSlots* InventorySlotSize.X)+ (TotalSlots - 1) * InventorySlotPadding.X;
	BoxSize.Y = InventorySlotSize.Y;
	SetBoxSize(BoxSize);
	
	for (int32 i = 0; i < TotalSlots; ++i)
	{
		UYdv_ItemSlot* NewSlot = CreateWidget<UYdv_ItemSlot>(this, InventorySlotClass);
		if (!IsValid(NewSlot)) continue;

		NewSlot->SetBoxSize(InventorySlotSize);
		InventoryHorizontalBox->AddChildToHorizontalBox(NewSlot);
		InventorySlots.Add(NewSlot);

		// Add a spacer after each slot (skip after the last one if desired)
		if (i < TotalSlots - 1)
		{
			USpacer* NewSpacer = NewObject<USpacer>(this);
			NewSpacer->SetSize(InventorySlotPadding);
			InventoryHorizontalBox->AddChildToHorizontalBox(NewSpacer);
		}

	}
}

void UYdv_ItemInventory::SetBoxSize(const FVector2D& NewSize) const
{
	if (IsValid(InventorySizeBox))
	{
		InventorySizeBox->SetWidthOverride(NewSize.X);
		InventorySizeBox->SetHeightOverride(NewSize.Y);
	}
}
