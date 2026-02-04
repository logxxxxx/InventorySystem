

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Composite/Ydv_CompositeBase.h"
#include "Ydv_Leaf.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UYdv_Leaf : public UYdv_CompositeBase
{
	GENERATED_BODY()
public:
	virtual void ApplyFunction(FuncType Function) override;
};
