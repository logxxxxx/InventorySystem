


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


void UYdv_ItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

