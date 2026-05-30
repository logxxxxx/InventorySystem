// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Ydv_InventoryItem.h"
#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "Item/Fragments/Ydv_ItemFragment.h"
#include "Net/UnrealNetwork.h"

UYdv_InventoryItem::UYdv_InventoryItem()
{
	if (IsValid(GetOuter()))
	{
		InventoryComponent = Cast<UYdv_InventoryComponent>(GetOuter());
	}
}

void UYdv_InventoryItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UYdv_InventoryItem, ItemManifest);
	DOREPLIFETIME(UYdv_InventoryItem, StackCount);
}

void UYdv_InventoryItem::SetItemManifest(const FYdv_ItemManifest& NewItemManifest)
{
	ItemManifest = FInstancedStruct::Make<FYdv_ItemManifest>(NewItemManifest);
}

void UYdv_InventoryItem::SetStackCount(int32 InCount)
{
	if (!InventoryComponent.IsValid()) return;
	if (InventoryComponent->GetOwner()->GetNetMode() == NM_ListenServer || InventoryComponent->GetOwner()->GetNetMode() == NM_Standalone)
	{
		StackCount = StackCount + InCount;
		if (FYdv_StackableFragment* StackFragment = GetItemManifest().GetFragmentOfTypeMutable<FYdv_StackableFragment>())
		{
			StackFragment->SetStackCount(StackCount);
		}
		InventoryComponent->OnInventoryItemStackCountChange.Broadcast(this, InCount);
		return;
	}
	Server_SetStackCount(StackCount);
}

void UYdv_InventoryItem::OnRep_StackCount(const int32& OldStackCount)
{
	if (!InventoryComponent.IsValid())
	{
		InventoryComponent->OnInventoryItemStackCountChange.Broadcast(this, OldStackCount-StackCount);
	}
}

void UYdv_InventoryItem::Server_SetStackCount_Implementation(int32 NewCount)
{
	StackCount = NewCount;
	if (FYdv_StackableFragment* StackFragment = GetItemManifest().GetFragmentOfTypeMutable<FYdv_StackableFragment>())
	{
		StackFragment->SetStackCount(NewCount);
	}
}
