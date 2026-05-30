

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Manifest/Ydv_ItemManifest.h"
#include "Ydv_ItemComponent.generated.h"




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable)
class INVENTORYSYSTEM_API UYdv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYdv_ItemComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void InitItemManifest(FYdv_ItemManifest CopyOfManifest);
	FYdv_ItemManifest GetItemManifest() const { return ItemManifest; }
	FYdv_ItemManifest& GetItemManifestMutable() { return ItemManifest; }
	
	void PickedUp();
private:
	UPROPERTY(EditAnywhere,Replicated, Category="Inventory")
	FYdv_ItemManifest ItemManifest;

protected:
	virtual void BeginPlay() override;
	
};

