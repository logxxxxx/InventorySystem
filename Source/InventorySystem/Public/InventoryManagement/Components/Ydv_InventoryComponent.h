

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Ydv_FastArray.h"
#include "Ydv_InventoryComponent.generated.h"

class UYdv_InventoryItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UYdv_InventoryItem* , Item);

UCLASS(ClassGroup=(Custom),Blueprintable, meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UYdv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYdv_InventoryComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddRepSubObject(UObject* SubObject);
	
public:
	FInventoryItemChange OnItemAddedToTheInventory;
	FInventoryItemChange OnItemRemovedFromTheInventory;

protected:
	virtual void BeginPlay() override;



private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(Replicated)
	FYdv_InventoryFastArray InventoryArrayList;

	UPROPERTY(EditAnywhere,Category = "Inventory")
	float TraceLength = 500.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "InventorySystem")
	TEnumAsByte<ECollisionChannel> TraceChannel;
	
	TWeakObjectPtr<AActor> CurrentActor;
	TWeakObjectPtr<AActor> PreviousActor;
	
private:
	void TraceForItems();
};
