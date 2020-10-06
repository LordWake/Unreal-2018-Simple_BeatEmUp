// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyUI.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALDNA_API AMyUI : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget *canvas;
	
	void virtual BeginPlay() override;
	void virtual Tick(float DeltaSeconds) override;
	
	void UpdatePlayerLife(float life);
	UFUNCTION(BlueprintCallable)
	void PlayerDead();
	UFUNCTION(BlueprintCallable)
	void PlayerWins();
	
};
