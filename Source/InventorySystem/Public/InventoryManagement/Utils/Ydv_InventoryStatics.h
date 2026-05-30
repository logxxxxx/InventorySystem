

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Ydv_InventoryStatics.generated.h"

class UYdv_InventoryComponent;

UCLASS()
class INVENTORYSYSTEM_API UYdv_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static UYdv_InventoryComponent* GetInventoryComponent(const APlayerController* PlayerController);
};
