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
class UYdv_CompositeBase;
USTRUCT(BlueprintType)
struct FYdv_InventoryItemFragment : public FYdv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UYdv_CompositeBase* Composite) const;
protected:
	bool MatchesWidgetTag(const UYdv_CompositeBase* Composite) const;
};

USTRUCT(BlueprintType)
struct FInv_TextFragment : public FYdv_InventoryItemFragment
{
	GENERATED_BODY()

	FText GetText() const { return FragmentText; }
	void SetText(const FText& Text) { FragmentText = Text; }
	virtual void Assimilate(UYdv_CompositeBase* Composite) const override;

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText FragmentText;
};
USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FYdv_InventoryItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetIcon() const { return Icon; }
	virtual void Assimilate(UYdv_CompositeBase* Composite) const override;

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconDimensions{44.f, 44.f};
};

USTRUCT(BlueprintType)
struct FYdv_StackableFragment : public FYdv_InventoryItemFragment
{
	GENERATED_BODY()

	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(int32 Count) { StackCount = Count; }
	virtual void Assimilate(UYdv_CompositeBase* Composite) const override;

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};
};