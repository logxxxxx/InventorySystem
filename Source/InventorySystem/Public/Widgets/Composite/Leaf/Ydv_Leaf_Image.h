

#pragma once

#include "CoreMinimal.h"
#include "Ydv_Leaf.h"
#include "Ydv_Leaf_Image.generated.h"

class UImage;
class USizeBox;
UCLASS()
class INVENTORYSYSTEM_API UYdv_Leaf_Image : public UYdv_Leaf
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable ,Category = "InventorySystem")
	void SetImage(UTexture2D* Texture) const;
	
protected:
	UFUNCTION( BlueprintCallable, Category = "InventorySystem")
	void SetSizeBoxSize();
	
	UFUNCTION(BlueprintCallable, Category = "InventorySystem" )
	void SetImageSize();
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "InventorySystem|ImageProperties", meta = (AllowPrivateAccess))
	FVector2D SizeBoxSize;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "InventorySystem|ImageProperties", meta = (AllowPrivateAccess))
	FDeprecateSlateVector2D ImageSize;
	
};
