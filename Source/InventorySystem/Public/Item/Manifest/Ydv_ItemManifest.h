#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTagContainer.h"
#include "Ydv_ItemManifest.generated.h"

class UYdv_CompositeBase;
struct FYdv_ItemFragment;
class UYdv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FYdv_ItemManifest
{
	GENERATED_BODY()
	
	UYdv_InventoryItem* ManifestItem(UObject* NewOuter) const;
	TArray<TInstancedStruct<FYdv_ItemFragment>>& GetFragmentsMutable() { return ItemFragments; }
	FGameplayTag GetItemTag() const { return ItemTag; }
	void AssimilateInventoryFragments(UYdv_CompositeBase* Composite) const;
	
	template<typename T> requires std::derived_from<T, FYdv_ItemFragment>
	const T* GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const;

	template<typename T> requires std::derived_from<T, FYdv_ItemFragment>
	const T* GetFragmentOfType() const;

	template<typename T> requires std::derived_from<T, FYdv_ItemFragment>
	T* GetFragmentOfTypeMutable();

	template<typename T> requires std::derived_from<T, FYdv_ItemFragment>
	TArray<const T*> GetAllFragmentsOfType() const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, Category = "Inventory" , meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FYdv_ItemFragment>> ItemFragments;
};

template<typename T>
requires std::derived_from<T, FYdv_ItemFragment>
const T* FYdv_ItemManifest::GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const
{
	for (const TInstancedStruct<FYdv_ItemFragment>& Fragment : ItemFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			if (!FragmentPtr->GetFragmentTag().MatchesTagExact(FragmentTag)) continue;
			return FragmentPtr;
		}
	}
	
	return nullptr;
}

template <typename T> requires std::derived_from<T, FYdv_ItemFragment>
const T* FYdv_ItemManifest::GetFragmentOfType() const
{
	for (const TInstancedStruct<FYdv_ItemFragment>& Fragment : ItemFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			return FragmentPtr;
		}
	}
	
	return nullptr;
}

template <typename T> requires std::derived_from<T, FYdv_ItemFragment>
T* FYdv_ItemManifest::GetFragmentOfTypeMutable()
{
	for (TInstancedStruct<FYdv_ItemFragment>& Fragment : ItemFragments)
	{
		if (T* FragmentPtr = Fragment.GetMutablePtr<T>())
		{
			return FragmentPtr;
		}
	}
	
	return nullptr;
}
template <typename T> requires std::derived_from<T, FYdv_ItemFragment>
TArray<const T*> FYdv_ItemManifest::GetAllFragmentsOfType() const
{
	TArray<const T*> Result;
	for (const TInstancedStruct<FYdv_ItemFragment>& Fragment : ItemFragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			Result.Add(FragmentPtr);
		}
	}
	return Result;
}