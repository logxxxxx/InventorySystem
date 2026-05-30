

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Composite/Ydv_Composite.h"
#include "Ydv_ItemSlot.generated.h"


class USizeBox;
class UImage;
class UYdv_InventoryItem;

UCLASS()
class INVENTORYSYSTEM_API UYdv_ItemSlot : public UYdv_Composite
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	void SetBoxSize(const FVector2D& NewSize) const;
	void SetInventoryItem(UYdv_InventoryItem* NewInventoryItem) {InventoryItem = NewInventoryItem;}
	UYdv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	void AddItemToSlot(UYdv_InventoryItem* ItemToAdd);
	void AddItemToSlot(UYdv_InventoryItem* ItemToAdd, const int32& InStackCount);
	void RemoveItemFromSlot(UYdv_InventoryItem* ItemToRemove);
	void UpdateStackCount(int32 NewStackCount);
	int32 GetStackCount() const {return StackCount;}
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
	UPROPERTY( meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;
	
	TWeakObjectPtr<UYdv_InventoryItem> InventoryItem;
	int32 StackCount{0};
	
protected:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnItemAddedToSlot(UYdv_InventoryItem* NewItem);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnItemRemovedFromSlot(UYdv_InventoryItem* ItemToRemove);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnStackCountUpdated(int32 NewStackCount);
	
};
