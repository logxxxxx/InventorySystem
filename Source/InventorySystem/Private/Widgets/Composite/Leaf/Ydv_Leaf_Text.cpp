


#include "Widgets/Composite/Leaf/Ydv_Leaf_Text.h"
#include "Components/TextBlock.h"

void UYdv_Leaf_Text::SetText(const FText& Text)
{
	Text_LeafText->SetText(Text);
}

void UYdv_Leaf_Text::SetTextFont()
{
	if (!IsValid(Text_LeafText)) return;
	FSlateFontInfo FontInfo;
	FontInfo.Size = TextSize;
	FontInfo.LetterSpacing = TextLetterSpacing;
	FontInfo.SkewAmount = TextSkewAmount;
	FontInfo.TypefaceFontName = TextTypefaceFontName;
	if (IsValid(FontObject))
	{
		FontInfo.FontObject = FontObject;
	}
	if (IsValid(TextFontMaterial))
	{
		FontInfo.FontMaterial = TextFontMaterial;
	}
	Text_LeafText->SetFont(FontInfo);
}

