

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ydv_InventoryOverlay.generated.h"


class UYdv_ItemInventory;
class UCanvasPanel;
UCLASS()
class INVENTORYSYSTEM_API UYdv_InventoryOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void ConstructItemInventory(int32 ItemSlots) const;
	
private:
	UPROPERTY(meta= (BindWidget))
	UCanvasPanel* InventoryCanvas;
	
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UYdv_ItemInventory> ItemInventory;
	
};
