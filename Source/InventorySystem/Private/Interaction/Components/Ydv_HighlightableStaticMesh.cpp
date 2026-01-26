// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Components/Ydv_HighlightableStaticMesh.h"

void UYdv_HighlightableStaticMesh::HighlightObject_Implementation()
{
	SetOverlayMaterial(HighlightMaterial);
}

void UYdv_HighlightableStaticMesh::UnHighlightObject_Implementation()
{
	SetOverlayMaterial(nullptr);
}
