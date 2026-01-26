

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ydv_InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom),Blueprintable, meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UYdv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYdv_InventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere,Category = "Inventory")
	float TraceLength = 500.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "InventorySystem")
	TEnumAsByte<ECollisionChannel> TraceChannel;
	
	TWeakObjectPtr<AActor> CurrentActor;
	TWeakObjectPtr<AActor> PreviousActor;
	
private:
	void TraceForItems();
};
