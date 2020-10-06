// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameOverUI.h"

void AMyGameOverUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}



