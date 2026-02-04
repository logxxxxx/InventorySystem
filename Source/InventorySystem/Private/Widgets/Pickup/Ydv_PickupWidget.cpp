


#include "Widgets/Pickup/Ydv_PickupWidget.h"

void UYdv_PickupWidget::SetVisibility(ESlateVisibility InVisibility)
{
	for (auto Child : GetChildren())
	{
		Child->Collapse();
	}
	Super::SetVisibility(InVisibility);
}
