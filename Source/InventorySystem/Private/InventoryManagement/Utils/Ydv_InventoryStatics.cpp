


#include "InventoryManagement/Utils/Ydv_InventoryStatics.h"

#include "InventoryManagement/Components/Ydv_InventoryComponent.h"

UYdv_InventoryComponent* UYdv_InventoryStatics::GetInventoryComponent(const APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return nullptr;
	UYdv_InventoryComponent* InventoryComponent = PlayerController->FindComponentByClass<UYdv_InventoryComponent>();
	return InventoryComponent;
}
