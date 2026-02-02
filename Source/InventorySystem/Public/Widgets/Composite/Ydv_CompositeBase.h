

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "Ydv_CompositeBase.generated.h"


UCLASS()
class INVENTORYSYSTEM_API UYdv_CompositeBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FGameplayTag GetFragmentTag() const { return WidgetFragmentTag; }
	void SetFragmentTag(const FGameplayTag& Tag) { WidgetFragmentTag = Tag; }
	virtual void Collapse();
	void Expand();

	using FuncType = TFunction<void(UYdv_CompositeBase*)>;
	virtual void ApplyFunction(FuncType Function) {}
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag WidgetFragmentTag;
};
