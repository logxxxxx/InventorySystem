

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Ydv_InteractionWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UYdv_InteractionWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UYdv_InteractionWidgetComponent();
	void ShowInteractionWidget(const AActor* Actor);
	void HideInteractionWidget();
	
private:
	void AssimilateInventoryWidget(const AActor* Actor) const;
	void SetInteractionWidgetVisibility(ESlateVisibility InVisibility) const;
};
