// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALDNA_API AMyMenuUI : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget*canvas;

	void virtual BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void StartGame();
	UFUNCTION(BlueprintCallable)
		void ShowHowToPlay();
	UFUNCTION(BlueprintCallable)
		void ShowCredits();
	UFUNCTION(BlueprintCallable)
		void BackButtonPressed();

};
