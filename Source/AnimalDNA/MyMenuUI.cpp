// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMenuUI.h"

void AMyMenuUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}

void AMyMenuUI::StartGame()
{
	if (canvas)
	canvas->aButtonPressed = true;
}

void AMyMenuUI::ShowCredits()
{
	if (canvas)
	canvas->yButtonPressed = true;
}

void AMyMenuUI::ShowHowToPlay()
{
	if (canvas)
	canvas->xButtonPressed = true;
}

void AMyMenuUI::BackButtonPressed()
{
	if (canvas)
	canvas->backButtonPressed = true;
}



