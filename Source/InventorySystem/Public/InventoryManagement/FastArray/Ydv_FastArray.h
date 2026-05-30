#pragma once
#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Ydv_FastArray.generated.h"

struct FGameplayTag;
class UYdv_ItemComponent;
class UYdv_InventoryItem;
class UYdv_InventoryComponent;

/**A struct representing a single item in the fast array*/
USTRUCT(BlueprintType)
struct FYdv_InventoryItemEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	FYdv_InventoryItemEntry(){}
	
private:
	friend struct FYdv_InventoryFastArray;
	friend UYdv_InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UYdv_InventoryItem> Item = nullptr;
	
};

/**A fast array struct for managing inventory items*/
USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FYdv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
	FYdv_InventoryFastArray():OwnerComponent(nullptr) {}
	FYdv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}
	
	TArray<UYdv_InventoryItem*> GetAllItems();
	
	/**Start FastArraySerializer Contract*/
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	/**End of FFastArraySerializer Contract*/
	
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FYdv_InventoryItemEntry, FYdv_InventoryFastArray>(Entries, DeltaParms, *this);
	}
	
	UYdv_InventoryItem* AddEntry(UYdv_InventoryItem* NewItem);
	UYdv_InventoryItem* AddEntry(UYdv_ItemComponent* NewItemComponent);
	void RemoveEntry(UYdv_InventoryItem* ItemToRemove);
	UYdv_InventoryItem* FindFirstItemByType(const FGameplayTag& ItemType);
private:
	friend UYdv_InventoryComponent;
	
	UPROPERTY()
	TArray<FYdv_InventoryItemEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

/** Necessary boilerplate to enable NetDeltaSerializer for FYdv_InventoryFastArray*/
template<>
struct TStructOpsTypeTraits<FYdv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FYdv_InventoryFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};