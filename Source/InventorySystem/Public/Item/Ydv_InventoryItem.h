// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Item/Manifest/Ydv_ItemManifest.h"
#include "Ydv_InventoryItem.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UYdv_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FYdv_ItemManifest GetItemManifest() const { return ItemManifest.Get<FYdv_ItemManifest>();}
	FYdv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FYdv_ItemManifest>(); }
	void SetItemManifest(const FYdv_ItemManifest& NewItemManifest);
private:
	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/InventorySystem.Ydv_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;
};

template <typename FragmentType>
const FragmentType* GetFragment(const UYdv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;

	const FYdv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWithTag<FragmentType>(Tag);
}