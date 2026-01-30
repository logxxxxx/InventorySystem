#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "Ydv_ItemManifest.generated.h"

struct FYdv_ItemFragment;
class UYdv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FYdv_ItemManifest
{
	GENERATED_BODY()
	
	UYdv_InventoryItem* ManifestItem(UObject* NewOuter) const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory" , meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FYdv_ItemFragment>> ItemFragments;
};