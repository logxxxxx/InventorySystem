#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Ydv_ItemFragment.generated.h"

USTRUCT(BlueprintType)
struct FYdv_ItemFragment
{
	GENERATED_BODY()

	FYdv_ItemFragment() {}
	FYdv_ItemFragment(const FYdv_ItemFragment &) = default;
	FYdv_ItemFragment& operator=(const FYdv_ItemFragment &) = default;
	FYdv_ItemFragment(FYdv_ItemFragment&&) = default;
	FYdv_ItemFragment& operator=(FYdv_ItemFragment&&) = default;
	virtual ~FYdv_ItemFragment() {}
	
	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag FragmentTag { FGameplayTag::EmptyTag};
	
};

/*
 * Item fragment specifically for assimilation into a widget.
 */
class UInv_CompositeBase;
USTRUCT(BlueprintType)
struct FYdv_InventoryItemFragment : public FYdv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UYdv_CompositeBase* Composite) const;
protected:
	bool MatchesWidgetTag(const UYdv_CompositeBase* Composite) const;
};