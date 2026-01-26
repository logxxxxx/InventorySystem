

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interaction/Ydv_Highlightable.h"
#include "Ydv_HighlightableStaticMesh.generated.h"


UCLASS()
class INVENTORYSYSTEM_API UYdv_HighlightableStaticMesh : public UStaticMeshComponent , public IYdv_Highlightable
{
	GENERATED_BODY()
	
public:
	virtual void HighlightObject_Implementation() override;
	
	virtual void UnHighlightObject_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
