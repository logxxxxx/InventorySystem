

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Manifest/Ydv_ItemManifest.h"
#include "Ydv_ItemComponent.generated.h"




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UYdv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYdv_ItemComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FYdv_ItemManifest GetItemManifest() const { return ItemManifest; }
private:
	UPROPERTY(EditAnywhere,Replicated, Category="Inventory")
	FYdv_ItemManifest ItemManifest;

protected:
	virtual void BeginPlay() override;
	
};
