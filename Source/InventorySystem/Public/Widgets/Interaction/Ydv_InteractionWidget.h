

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Composite/Ydv_Composite.h"
#include "Ydv_InteractionWidget.generated.h"

class UYdv_ItemComponent;
class UYdv_InventoryComponent;
class USizeBox;

UCLASS()
class INVENTORYSYSTEM_API UYdv_InteractionWidget : public UYdv_Composite
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	FAnchors GetPickupWidgetAnchors() const { return PickupWidgetAnchors; }
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FAnchors PickupWidgetAnchors {1.0f, 1.0f};
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void UpdateStackCount(int32 NewStackCount);
private:
	UFUNCTION()
	void OnStackCountChanged(UYdv_ItemComponent* ItemComponent, int32 NewStackCount);
};
