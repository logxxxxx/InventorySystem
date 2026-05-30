


#include "Widgets/Composite/Leaf/Ydv_Leaf_Image.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"

void UYdv_Leaf_Image::SetImage(UTexture2D* Texture) const
{
	if (!IsValid(Image_Icon)) return;
	Image_Icon->SetBrushFromTexture(Texture);
}

void UYdv_Leaf_Image::SetSizeBoxSize()
{
	if (!IsValid(SizeBox_Icon)) return;
	SizeBox_Icon->SetHeightOverride(SizeBoxSize.Y);
	SizeBox_Icon->SetWidthOverride(SizeBoxSize.X);
}

void UYdv_Leaf_Image::SetImageSize()
{
	if (!IsValid(Image_Icon)) return;
	FSlateBrush Brush;
	Brush.ImageSize = ImageSize;
	Image_Icon->SetBrush(Brush);
}
