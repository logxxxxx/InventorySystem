// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Ydv_InventoryItem.h"
#include "Net/UnrealNetwork.h"

void UYdv_InventoryItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UYdv_InventoryItem, ItemManifest);
}

void UYdv_InventoryItem::SetItemManifest(const FYdv_ItemManifest& NewItemManifest)
{
	ItemManifest = FInstancedStruct::Make<FYdv_ItemManifest>(NewItemManifest);
}
