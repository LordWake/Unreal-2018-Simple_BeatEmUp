// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyGameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALDNA_API AMyGameOverUI : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget*canvas;
	
	void virtual BeginPlay() override;
};
