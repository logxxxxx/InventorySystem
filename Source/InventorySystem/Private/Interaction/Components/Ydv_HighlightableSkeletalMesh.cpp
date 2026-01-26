// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Components/Ydv_HighlightableSkeletalMesh.h"

void UYdv_HighlightableSkeletalMesh::HighlightObject_Implementation()
{
	SetOverlayMaterial(HighlightMaterial);
}

void UYdv_HighlightableSkeletalMesh::UnHighlightObject_Implementation()
{
	SetOverlayMaterial(nullptr);
}
