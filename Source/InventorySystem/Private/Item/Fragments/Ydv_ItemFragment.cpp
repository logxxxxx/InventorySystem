#include "Item/Fragments/Ydv_ItemFragment.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"
#include "Widgets/Composite/Leaf/Ydv_Leaf_Image.h"
#include "Widgets/Composite/Leaf/Ydv_Leaf_Text.h"

void FYdv_InventoryItemFragment::Assimilate(UYdv_CompositeBase* Composite) const
{
	if (!MatchesWidgetTag(Composite)) return;
	Composite->Expand();
}

bool FYdv_InventoryItemFragment::MatchesWidgetTag(const UYdv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}

void FInv_TextFragment::Assimilate(UYdv_CompositeBase* Composite) const
{
	FYdv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return ;
	
	UYdv_Leaf_Text* LeafText = Cast<UYdv_Leaf_Text>(Composite);
	if (!IsValid(LeafText)) return;
	LeafText->SetText(FragmentText);
}

void FInv_ImageFragment::Assimilate(UYdv_CompositeBase* Composite) const
{
	FYdv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return ;
	
	UYdv_Leaf_Image* Image = Cast<UYdv_Leaf_Image>(Composite);
	if (!IsValid(Image)) return;
	
	Image->SetImage(Icon);
	Image->SetBoxSize(IconDimensions);
	Image->SetImageSize(IconDimensions);
}
