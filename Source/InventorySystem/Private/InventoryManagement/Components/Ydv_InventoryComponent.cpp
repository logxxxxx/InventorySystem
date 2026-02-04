


#include "InventoryManagement/Components/Ydv_InventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Interaction/Ydv_Highlightable.h"
#include "Interaction/Components/Ydv_InteractionWidget.h"
#include "Kismet/GameplayStatics.h"


UYdv_InventoryComponent::UYdv_InventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	
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
	if (CurrentActor == PreviousActor) return;
	
	if (CurrentActor.IsValid())
	{
		ShowInteractionItem(CurrentActor.Get());
	}
	if (PreviousActor.IsValid())
	{
		HideInteractionItem(PreviousActor.Get());
	}
}

void UYdv_InventoryComponent::ShowInteractionItem(AActor* Actor) const
{
	if (!IsValid(Actor)) return;
	if (UActorComponent* HighlightableComponent =  Actor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
	{
		IYdv_Highlightable::Execute_HighlightObject(HighlightableComponent);
	}
	if (UYdv_InteractionWidget* InteractionWidget = Actor->FindComponentByClass<UYdv_InteractionWidget>(); IsValid(InteractionWidget))
	{
		InteractionWidget->ShowInteractionWidget();
	}
	
}

void UYdv_InventoryComponent::HideInteractionItem(AActor* Actor) const
{
	if (!IsValid(Actor)) return;
	if (UActorComponent* HighlightableComponent =  Actor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
	{
		IYdv_Highlightable::Execute_UnHighlightObject(HighlightableComponent);
	}
	if (UYdv_InteractionWidget* InteractionWidget = Actor->FindComponentByClass<UYdv_InteractionWidget>(); IsValid(InteractionWidget))
	{
		InteractionWidget->HideInteractionWidget();
	}
}


