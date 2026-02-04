

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Ydv_InteractionWidget.generated.h"

class UYdv_CompositeBase;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UYdv_InteractionWidget : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UYdv_InteractionWidget();
	
	void ShowInteractionWidget();
	void HideInteractionWidget();
	
private:
	TWeakObjectPtr<UYdv_CompositeBase> InteractionWidget;
	
	void AssimilateInventoryWidget();

};
