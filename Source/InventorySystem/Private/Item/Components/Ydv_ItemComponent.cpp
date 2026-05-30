


#include "Item/Components/Ydv_ItemComponent.h"
#include "Net/UnrealNetwork.h"


UYdv_ItemComponent::UYdv_ItemComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}

void UYdv_ItemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UYdv_ItemComponent, ItemManifest);
}

void UYdv_ItemComponent::InitItemManifest(FYdv_ItemManifest CopyOfManifest)
{
	ItemManifest = CopyOfManifest;
}


void UYdv_ItemComponent::PickedUp()
{
	//Print string to the screen 
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Item Picked up");
	}
	if (AActor* OwnerActor = GetOwner(); IsValid(OwnerActor))
	{
		OwnerActor->Destroy();
	}
}

void UYdv_ItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

