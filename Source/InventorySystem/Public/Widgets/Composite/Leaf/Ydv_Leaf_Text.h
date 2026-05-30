

#pragma once

#include "CoreMinimal.h"
#include "Ydv_Leaf.h"
#include "Ydv_Leaf_Text.generated.h"


class UTextBlock;

UCLASS()
class INVENTORYSYSTEM_API UYdv_Leaf_Text : public UYdv_Leaf
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION( BlueprintCallable, Category = "InventorySystem" )
	void SetText(const FText& Text);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(AllowedClasses="/Script/Engine.Font", DisplayName="Text Font Family"))
	TObjectPtr<const UObject> FontObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(AllowedClasses="/Script/Engine.MaterialInterface"))
	TObjectPtr<UObject> TextFontMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(DisplayName="Typeface", EditCondition="FontObject"))
	FName TextTypefaceFontName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(ClampMin=1, ClampMax=1000))
	float TextSize =14;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(ClampMin=-1000, ClampMax=10000))
	int32 TextLetterSpacing = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InventorySystem|FontProperties", meta=(ClampMin=-5, ClampMax=5))
	float TextSkewAmount = 0.0f;
	
	UFUNCTION(BlueprintCallable, Category = "InventorySystem")
	void SetTextFont();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_LeafText;
	
};
