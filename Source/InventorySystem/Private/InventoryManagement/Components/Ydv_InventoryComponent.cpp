


#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/HUD.h"
#include "Net/UnrealNetwork.h"
#include "Interaction/Ydv_Highlightable.h"
#include "InventoryManagement/Ydv_InventorySystemInterface.h"
#include "Interaction/Components/Ydv_InteractionWidgetComponent.h"
#include "InventoryManagement/Types/Ydv_InventoryTypes.h"
#include "Item/Ydv_InventoryItem.h"
#include "Item/Components/Ydv_ItemComponent.h"
#include "Item/Fragments/Ydv_ItemFragment.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Ydv_InventoryOverlay.h"
#include "Widgets/Item/Ydv_ItemInventory.h"
#include "Widgets/Interaction/Ydv_InteractionWidget.h"


UYdv_InventoryComponent::UYdv_InventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	InventoryArrayList.OwnerComponent = this;
	
}

void UYdv_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UYdv_InventoryComponent, InventoryArrayList);
}


void UYdv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		PlayerController = Cast<APlayerController>(GetOwner());
		check(PlayerController);
		
		//Construct the Inventory Overlay
		CreateInventoryOverlay();
		
		// Create Pickup Widget 
		CreateInteractionWidget();
	}
	
}


void UYdv_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceForItems();
}

void UYdv_InventoryComponent::AddRepSubObject(UObject* SubObject)
{
	if (IsUsingRegisteredSubObjectList() && IsValid(SubObject) && IsReadyForReplication())
	{
		AddReplicatedSubObject(SubObject);
	}
	
}

void UYdv_InventoryComponent::TraceForItems()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport) || !IsValid(PlayerController)) return;
	
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ScreenCenter = FVector2D(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	
	FVector TraceStart, TraceDirection;
	UGameplayStatics::DeprojectScreenToWorld(PlayerController,ScreenCenter,TraceStart,TraceDirection);
	FVector TraceEnd = TraceStart + (TraceDirection * TraceLength);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,TraceChannel);
	
	PreviousActor = CurrentActor;
	CurrentActor = HitResult.GetActor();
	if (!CurrentActor.IsValid())
	{
		if (IsValid(InteractionWidgetComponent))
		{
			InteractionWidgetComponent->HideInteractionWidget();
		}
	}
	if (CurrentActor == PreviousActor) return;
	
	if (CurrentActor.IsValid())
	{
		ShowInteractionItem(CurrentActor.Get());
		return;
	}
	if (PreviousActor.IsValid())
	{
		HideInteractionItem(PreviousActor.Get());
	}
	
}

void UYdv_InventoryComponent::CreateInteractionWidget()
{
	if (!IsValid(PlayerController)) return;
	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!IsValid(PlayerPawn)) return;
	
	UActorComponent* NewComp = PlayerPawn->AddComponentByClass(UYdv_InteractionWidgetComponent::StaticClass(),
		true,FTransform(),false);
	if (!IsValid(NewComp)) return;
	
	InteractionWidgetComponent = Cast<UYdv_InteractionWidgetComponent>(NewComp);
	if (!IsValid(InteractionWidgetComponent) || !IsValid(InteractionWidgetClass)) return;
	InteractionWidgetComponent->SetWidgetClass(InteractionWidgetClass);
}

void UYdv_InventoryComponent::ShowInteractionItem(const AActor* Actor) const
{
	if (!IsValid(Actor)) return;
	if (UActorComponent* HighlightableComponent =  Actor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
	{
		IYdv_Highlightable::Execute_HighlightObject(HighlightableComponent);
	}
	if (IsValid(InteractionWidgetComponent))
	{
		InteractionWidgetComponent->ShowInteractionWidget(Actor);
	}
	
}

void UYdv_InventoryComponent::HideInteractionItem(const AActor* Actor) const
{
	if (!IsValid(Actor)) return;
	if (UActorComponent* HighlightableComponent =  Actor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
	{
		IYdv_Highlightable::Execute_UnHighlightObject(HighlightableComponent);
	}
	if (IsValid(InteractionWidgetComponent))
	{
		InteractionWidgetComponent->HideInteractionWidget();
	}
}

void UYdv_InventoryComponent::CreateInventoryOverlay()
{
	if (!IsValid(ItemInventoryClass) || IsValid(ItemInventory) || TotalNumberOfItemSlots <= 0) return;
	if (!IsValid(PlayerController)) return;
	if (!IsValid(PlayerController->GetHUD())) return;
	
	UCanvasPanel* CanvasPanel = Cast<IYdv_InventorySystemInterface>(PlayerController->GetHUD())->GetOverlayCanvas();
	if (!IsValid(CanvasPanel)) return;
	
	ItemInventory = CreateWidget<UYdv_ItemInventory>(PlayerController.Get(), ItemInventoryClass);
	if (!IsValid(ItemInventory)) return;
	CanvasPanel->AddChild(ItemInventory);
	ItemInventory->ConstructItemSlots(TotalNumberOfItemSlots);
	
	UCanvasPanelSlot* ItemInventoryCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemInventory);
	if (!IsValid(ItemInventoryCPS)) return;
	
	ItemInventoryCPS->SetAnchors(ItemInventory->GetItemInventoryAnchors());
	ItemInventoryCPS->SetAlignment(ItemInventory->GetItemInventoryAlignment());
	ItemInventoryCPS->SetAutoSize(true);
	
}

void UYdv_InventoryComponent::TryAddItem(UYdv_ItemComponent* ItemComponent)
{
	const FYdv_InventoryAvailabilityResult& InventoryAvailabilityResult = GetInventoryAvailabilityResult(ItemComponent);
	if (InventoryAvailabilityResult.bStackable)
	{
		if (InventoryAvailabilityResult.Item.IsValid())
		{
			Server_AddStackToInventoryItem(ItemComponent,InventoryAvailabilityResult.Item.Get(),
			InventoryAvailabilityResult.TotalRoomToFill, InventoryAvailabilityResult.Remainder);
			return;
		}
	}
	Server_AddItemToInventory(ItemComponent, InventoryAvailabilityResult.TotalRoomToFill, InventoryAvailabilityResult.Remainder);
}

FYdv_InventoryAvailabilityResult UYdv_InventoryComponent::GetInventoryAvailabilityResult(const UYdv_ItemComponent* ItemComponent)
{
	FYdv_InventoryAvailabilityResult Result;

	const FYdv_StackableFragment* StackableFragment = ItemComponent->GetItemManifest().GetFragmentOfType<FYdv_StackableFragment>();
	Result.bStackable = StackableFragment != nullptr;

	// Non-stackable item: always takes exactly 1 slot
	if (!Result.bStackable)
	{
		Result.TotalRoomToFill = 1;
		return Result;
	}

	const int32 AvailableStackCount = StackableFragment->GetStackCount();
	const int32 MaxStackCount = StackableFragment->GetMaxStackSize();
	UYdv_InventoryItem* FoundItem = InventoryArrayList.FindFirstItemByType(ItemComponent->GetItemManifest().GetItemTag());
	if (!IsValid(FoundItem))
	{
		// No existing stack — fill entirely into a new slot
		Result.TotalRoomToFill = FMath::Min(AvailableStackCount,MaxStackCount);
		Result.Remainder = FMath::Max(0,AvailableStackCount - MaxStackCount);
		return Result;
	}

	// Merge into the existing stack
	Result.Item = FoundItem;
	const FYdv_StackableFragment* FoundStackFragment = FoundItem->GetItemManifest().GetFragmentOfType<FYdv_StackableFragment>();
	const int32 SpaceRemaining = FoundStackFragment->GetMaxStackSize() - FoundItem->GetStackCount()% MaxStackCount;
	
	if (SpaceRemaining <= 0)
	{
		// Existing stack is already full — fill entirely into a new slot
		Result.TotalRoomToFill = FMath::Min(AvailableStackCount,MaxStackCount);
		Result.Remainder = FMath::Max(0,AvailableStackCount - MaxStackCount);
		return Result;
	}
	Result.TotalRoomToFill = FMath::Min(SpaceRemaining, AvailableStackCount);
	Result.Remainder       = FMath::Max(0, AvailableStackCount - SpaceRemaining);
	return Result;
	
}

void UYdv_InventoryComponent::Server_AddStackToInventoryItem_Implementation(UYdv_ItemComponent* ItemComponent,UYdv_InventoryItem* FoundItem, int32 StackCountToAdd, int32 Remainder)
{
	if (!IsValid(FoundItem) || !IsValid(ItemComponent)) return;
	FoundItem->SetStackCount(StackCountToAdd);
	
	if (Remainder == 0)
	{
		ItemComponent->PickedUp();
	}
	else if (FYdv_StackableFragment* StackableFragment = ItemComponent->GetItemManifestMutable().GetFragmentOfTypeMutable<FYdv_StackableFragment>())
	{
		StackableFragment->SetStackCount(Remainder);
		OnPickupItemStackCountChange.Broadcast(ItemComponent, Remainder);
	}
}

void UYdv_InventoryComponent::Server_AddItemToInventory_Implementation(UYdv_ItemComponent* ItemComponent, int32 StackCountToAdd, int32 Remainder)
{
	if (UYdv_InventoryItem* NewItem = InventoryArrayList.AddEntry(ItemComponent); IsValid(NewItem))
	{
		NewItem->SetStackCount(StackCountToAdd);
		
		if (GetOwner()->GetNetMode() == NM_ListenServer || GetOwner()->GetNetMode() == NM_Standalone)
		{
			OnItemAddedToTheInventory.Broadcast(NewItem);
		}
		
		if (Remainder == 0)
		{
			ItemComponent->PickedUp();
		}
		else if (FYdv_StackableFragment* StackableFragment = ItemComponent->GetItemManifestMutable().GetFragmentOfTypeMutable<FYdv_StackableFragment>())
		{
			StackableFragment->SetStackCount(Remainder);
			OnPickupItemStackCountChange.Broadcast(ItemComponent, Remainder);
		}
		
	}
}


