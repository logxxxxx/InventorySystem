


#include "Widgets/Composite/Ydv_CompositeBase.h"

void UYdv_CompositeBase::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UYdv_CompositeBase::Expand()
{
	SetVisibility(ESlateVisibility::Visible);
}
