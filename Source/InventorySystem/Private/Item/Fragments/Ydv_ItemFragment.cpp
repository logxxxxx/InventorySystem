#include "Item/Fragments/Ydv_ItemFragment.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"

void FYdv_InventoryItemFragment::Assimilate(UYdv_CompositeBase* Composite) const
{
	if (!MatchesWidgetTag(Composite)) return;
	Composite->Expand();
}

bool FYdv_InventoryItemFragment::MatchesWidgetTag(const UYdv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}
