// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interaction/Ydv_Highlightable.h"
#include "Ydv_HighlightableSkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UYdv_HighlightableSkeletalMesh : public USkeletalMeshComponent, public IYdv_Highlightable
{
	GENERATED_BODY()
	
public:
	virtual void HighlightObject_Implementation() override;
	
	virtual void UnHighlightObject_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
