// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Item/Manifest/Ydv_ItemManifest.h"
#include "Ydv_InventoryItem.generated.h"

class UYdv_InventoryComponent;

UCLASS()
class INVENTORYSYSTEM_API UYdv_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	UYdv_InventoryItem();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FYdv_ItemManifest GetItemManifest() const { return ItemManifest.Get<FYdv_ItemManifest>();}
	FYdv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FYdv_ItemManifest>(); }
	void SetItemManifest(const FYdv_ItemManifest& NewItemManifest);
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(int32 Count);
private:
	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/InventorySystem.Ydv_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;
	
	TWeakObjectPtr<UYdv_InventoryComponent> InventoryComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_StackCount)
	int32 StackCount{0};
	
	UFUNCTION()
	void OnRep_StackCount(const int32& OldStackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_SetStackCount(int32 Count);
};

template <typename FragmentType>
const FragmentType* GetFragment(const UYdv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;

	const FYdv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWithTag<FragmentType>(Tag);
}