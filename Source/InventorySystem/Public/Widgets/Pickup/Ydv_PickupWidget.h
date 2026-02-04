

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Composite/Ydv_Composite.h"
#include "Ydv_PickupWidget.generated.h"

class USizeBox;

UCLASS()
class INVENTORYSYSTEM_API UYdv_PickupWidget : public UYdv_Composite
{
	GENERATED_BODY()
	
public:
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
};
