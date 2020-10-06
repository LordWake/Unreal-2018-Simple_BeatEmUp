// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALDNA_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerHUDlife;
	
	UPROPERTY(BlueprintReadWrite)
	bool playerIsDead;

	UPROPERTY(BlueprintReadWrite)
	bool playerWin;

	UPROPERTY(BlueprintReadWrite)
	bool aButtonPressed;

	UPROPERTY(BlueprintReadWrite)
	bool xButtonPressed;

	UPROPERTY(BlueprintReadWrite)
	bool yButtonPressed;

	UPROPERTY(BlueprintReadWrite)
	bool backButtonPressed;

	UPROPERTY(BlueprintReadWrite)
	bool resetThisLevel;	
};
