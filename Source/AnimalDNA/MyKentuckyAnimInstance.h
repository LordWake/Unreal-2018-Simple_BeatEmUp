// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "MyKentuckyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALDNA_API UMyKentuckyAnimInstance : public UAnimInstance
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
		bool thirdDamageAnimation;
	
	UPROPERTY(BlueprintReadOnly)
		bool bossIsDead;

	UPROPERTY(BlueprintReadOnly)
		bool bossIsNotAttacking;

	UPROPERTY(BlueprintReadOnly)
		bool firstAttack;

	UPROPERTY(BlueprintReadOnly)
		bool secondAttack;

	UPROPERTY(BlueprintReadOnly)
		bool thirdAttack;

	UPROPERTY(BlueprintReadOnly)
		bool specialOne;

	UPROPERTY(BlueprintReadOnly)
		bool specialTwo;

	void SetBossDamage(int damageNumber);
	void SetBossDead();
	void SetBossMovement(bool movement);
	void SetBossAttack(int attackNumber);

	UFUNCTION(BlueprintCallable)
		void OnBossDamageFinish();

	UFUNCTION(BlueprintCallable)
		void StartAttackEvent();

	UFUNCTION(BlueprintCallable)
		void StartHardAttackEvent();

	UFUNCTION(BlueprintCallable)
		void DisableAttackCollider();

	UFUNCTION(BlueprintCallable)
		void EndAttackEvent();
	
};
