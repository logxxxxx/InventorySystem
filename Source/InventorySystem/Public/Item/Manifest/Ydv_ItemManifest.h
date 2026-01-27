#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "Ydv_ItemManifest.generated.h"

class UYdv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FYdv_ItemManifest
{
	GENERATED_BODY()
	
	UYdv_InventoryItem* ManifestItem(UObject* NewOuter) const;
};