

#pragma once

#include "CoreMinimal.h"
#include "Ydv_CompositeBase.h"
#include "Ydv_Composite.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UYdv_Composite : public UYdv_CompositeBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void ApplyFunction(FuncType Function) override;
	virtual void Collapse() override;
	virtual void Expand() override;
	TArray<UYdv_CompositeBase*> GetChildren() { return Children; }
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UYdv_CompositeBase>> Children;
};
