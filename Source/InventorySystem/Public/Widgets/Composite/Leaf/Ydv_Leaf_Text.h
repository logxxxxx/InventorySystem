

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
	void SetText(const FText& Text) const;
	virtual void NativePreConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_LeafText;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 FontSize{14};
};
