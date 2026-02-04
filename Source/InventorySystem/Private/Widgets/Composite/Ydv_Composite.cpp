


#include "Widgets/Composite/Ydv_Composite.h"

#include "Blueprint/WidgetTree.h"

void UYdv_Composite::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	WidgetTree->ForEachWidget([this](UWidget* Widget)
{
	if (UYdv_CompositeBase* Composite = Cast<UYdv_CompositeBase>(Widget); IsValid(Composite))
	{
		Children.Add(Composite);
		Composite->Collapse();
	}
});
}

void UYdv_Composite::ApplyFunction(FuncType Function)
{
	for (auto& Child : Children)
	{
		Child->ApplyFunction(Function);
	}
}

void UYdv_Composite::Collapse()
{
	for (auto& Child : Children)
	{
		Child->Collapse();
	}
}

void UYdv_Composite::Expand()
{
	for (auto& Child : Children)
	{
		Child->Expand();
	}
}
