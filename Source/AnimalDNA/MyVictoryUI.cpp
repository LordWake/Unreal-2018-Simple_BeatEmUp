// Fill out your copyright notice in the Description page of Project Settings.

#include "MyVictoryUI.h"

void AMyVictoryUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}



