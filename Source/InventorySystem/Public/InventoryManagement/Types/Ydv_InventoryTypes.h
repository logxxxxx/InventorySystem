#pragma once
#include "CoreMinimal.h"
#include "Ydv_InventoryTypes.generated.h"


class UYdv_InventoryItem;

USTRUCT()
struct FYdv_InventoryAvailabilityResult
{
	GENERATED_BODY()
	
	TWeakObjectPtr<UYdv_InventoryItem> Item;
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
	bool bStackable{false};
};