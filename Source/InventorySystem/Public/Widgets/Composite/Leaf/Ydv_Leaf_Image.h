

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
	void SetImage(UTexture2D* Texture) const;
	void SetBoxSize(const FVector2D& Size) const;
	void SetImageSize(const FVector2D& Size) const;
	FVector2D GetImageSize() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Icon;
};
