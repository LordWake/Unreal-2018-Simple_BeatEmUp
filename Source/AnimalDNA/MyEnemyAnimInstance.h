// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "MyEnemyAnimInstance.generated.h"

UCLASS()
class ANIMALDNA_API UMyEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:


	UPROPERTY(BlueprintReadOnly)
	bool isMoving;

	UPROPERTY(BlueprintReadOnly)
	bool firstDamageAnimation;

	UPROPERTY(BlueprintReadOnly)
	bool secondDamageAnimation;
	
	UPROPERTY(BlueprintReadOnly)
	bool enemyIsDead;

	UPROPERTY(BlueprintReadOnly)
	bool enemyIsNotAttackin;

	UPROPERTY(BlueprintReadOnly)
	bool firstAttack;

	UPROPERTY(BlueprintReadOnly)
	bool secondAttack;

	UPROPERTY(BlueprintReadOnly)
	bool thirdAttack;


	void SetEnemyDamage(int damageNumber);
	void SetEnemyDead();
	void SetEnemyMovement(bool movement);
	void SetEnemyAttack(int attackNumber);
	
	UFUNCTION(BlueprintCallable)
	void OnDamageFinish();
	
	UFUNCTION(BlueprintCallable)
	void StartAttackEvent();

	UFUNCTION(BlueprintCallable)
	void EndAttackEvent();

	UFUNCTION(BlueprintCallable)
	void DisableAttackCollider();
	
};
