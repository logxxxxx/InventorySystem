

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Ydv_FastArray.h"
#include "InventoryManagement/Types/Ydv_InventoryTypes.h"
#include "Ydv_InventoryComponent.generated.h"

class UYdv_InteractionWidgetComponent;
class UYdv_ItemInventory;
class UYdv_InventoryOverlay;
class UYdv_InventoryItem;
class UYdv_InteractionWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UYdv_InventoryItem* , Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryItemStackCountChange, UYdv_InventoryItem*, Item, int32, NewStackCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPickupItemStackCountChange, UYdv_ItemComponent*, ItemComponent, int32, NewStackCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventory);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class INVENTORYSYSTEM_API UYdv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYdv_InventoryComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	void AddRepSubObject(UObject* SubObject);
	
	AActor* GetCurrentActor() const {return CurrentActor.Get();}
	void TryAddItem(UYdv_ItemComponent* ItemComponent);

	FInventoryItemChange OnItemAddedToTheInventory;
	FInventoryItemChange OnItemRemovedFromTheInventory;
	FInventoryItemStackCountChange OnInventoryItemStackCountChange;
	FPickupItemStackCountChange OnPickupItemStackCountChange;
	FNoRoomInInventory NoRoomInInventory;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(Replicated)
	FYdv_InventoryFastArray InventoryArrayList;

	UPROPERTY(EditAnywhere,Category = "Inventory")
	float TraceLength = 500.f;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> TraceChannel;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UYdv_InteractionWidget> InteractionWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UYdv_ItemInventory> ItemInventoryClass;
	
	UPROPERTY()
	TObjectPtr<UYdv_ItemInventory> ItemInventory;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 TotalNumberOfItemSlots {5};
	
	
	TWeakObjectPtr<AActor> CurrentActor;
	TWeakObjectPtr<AActor> PreviousActor;
	
	UPROPERTY()
	TObjectPtr<UYdv_InteractionWidgetComponent> InteractionWidgetComponent;
	
	void TraceForItems();
	void CreateInteractionWidget();
	void ShowInteractionItem(const AActor* Actor) const;
	void HideInteractionItem(const AActor* Actor) const;
	void CreateInventoryOverlay();
	FYdv_InventoryAvailabilityResult GetInventoryAvailabilityResult(const UYdv_ItemComponent* ItemComponent);
	
	
	UFUNCTION(Server,Reliable)
	void Server_AddItemToInventory(UYdv_ItemComponent* ItemComponent, int32 StackCountToAdd, int32 Remainder);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStackToInventoryItem(UYdv_ItemComponent* ItemComponent,UYdv_InventoryItem* FoundItem, int32 StackCountToAdd, int32 Remainder);
	
};
