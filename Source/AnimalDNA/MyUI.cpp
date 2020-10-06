// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUI.h"

void AMyUI::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);
	if (canvas)
		canvas->AddToViewport();
}

void AMyUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyUI::UpdatePlayerLife(float life)
{
	if(canvas)
	canvas->playerHUDlife = life;
}

void AMyUI::PlayerDead()
{
	if (canvas)
		canvas->playerIsDead = true;
}

void AMyUI::PlayerWins()
{
	if (canvas)
		canvas->playerWin = true;
}

