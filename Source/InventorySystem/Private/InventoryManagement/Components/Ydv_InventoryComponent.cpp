


#include "InventoryManagement/Components/Ydv_InventoryComponent.h"

#include "Interaction/Ydv_Highlightable.h"
#include "Kismet/GameplayStatics.h"


UYdv_InventoryComponent::UYdv_InventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	
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
		UE_LOG(LogTemp, Warning, TEXT("TraceForItems %s"), *CurrentActor->GetName());
		if (UActorComponent* HighlightableComponent =  CurrentActor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
		{
			IYdv_Highlightable::Execute_HighlightObject(HighlightableComponent);
		}
	}
	if (PreviousActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Lost TraceForItems %s"), *PreviousActor->GetName());
		if (UActorComponent* HighlightableComponent =  PreviousActor->FindComponentByInterface(UYdv_Highlightable::StaticClass());IsValid(HighlightableComponent))
		{
			IYdv_Highlightable::Execute_UnHighlightObject(HighlightableComponent);
		}
	}
}

