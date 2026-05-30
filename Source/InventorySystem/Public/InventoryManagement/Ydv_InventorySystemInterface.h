// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ydv_InventorySystemInterface.generated.h"

class UCanvasPanel;
// This class does not need to be modified.
UINTERFACE()
class UYdv_InventorySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYSYSTEM_API IYdv_InventorySystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual UCanvasPanel* GetOverlayCanvas() const = 0;
};
