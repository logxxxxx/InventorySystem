

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ydv_Highlightable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UYdv_Highlightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYSYSTEM_API IYdv_Highlightable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, Category="Inventory")
	void HighlightObject();
	
	UFUNCTION(BlueprintNativeEvent, Category="Inventory")
	void UnHighlightObject();
	
};
