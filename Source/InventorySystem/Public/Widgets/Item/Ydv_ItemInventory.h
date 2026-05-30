

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ydv_ItemInventory.generated.h"

class USizeBox;
class UHorizontalBox;
class UYdv_InventoryItem;
class UYdv_ItemSlot;

UCLASS()
class INVENTORYSYSTEM_API UYdv_ItemInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	void AddItemToInventorySlot(UYdv_InventoryItem* ItemToAdd);
	void AddItemToInventorySlot(UYdv_InventoryItem* ItemToAdd, int32 StackCount);
	void ConstructItemSlots(const int32& TotalSlots);
	FAnchors GetItemInventoryAnchors() const { return ItemInventoryAnchors; }
	FVector2D GetItemInventoryAlignment() const { return ItemInventoryAlignment; }
	
private:
	
	UPROPERTY(meta= (BindWidget))
	USizeBox* InventorySizeBox;
	
	UPROPERTY(meta= (BindWidget))
	UHorizontalBox* InventoryHorizontalBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UYdv_ItemSlot> InventorySlotClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FVector2D InventorySlotSize {100.f, 100.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FVector2D InventorySlotPadding {15.f, 0.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FAnchors ItemInventoryAnchors {0.5f, 1.f};
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FVector2D ItemInventoryAlignment {0.5f, 0.75f};
	
	UPROPERTY()
	TArray<TObjectPtr<UYdv_ItemSlot>> InventorySlots;
	
	UFUNCTION()
	void OnItemAddedToInventory(UYdv_InventoryItem* ItemToAdd);
	
	UFUNCTION()
	void OnStackCountChange(UYdv_InventoryItem* Item, int32 InStackCount);
	
	void SetBoxSize(const FVector2D& NewSize) const;
	
};
