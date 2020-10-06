#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class ANIMALDNA_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

		UPROPERTY(BlueprintReadOnly)
		FVector2D playerDirection;

		UPROPERTY(BlueprintReadOnly)
		bool playerIsBlocking;

		UPROPERTY(BlueprintReadOnly)
		bool firstDamage;

		UPROPERTY(BlueprintReadOnly)
		bool secondDamage;

		UPROPERTY(BlueprintReadOnly)
		bool thirdDamage;

		UPROPERTY(BlueprintReadOnly)
		bool onDamageFinish;

		UPROPERTY(BlueprintReadOnly)
		bool onPlayerDead;

#pragma region PlayerAttackBool
		UPROPERTY(BlueprintReadWrite)
			bool playerIsNotAttacking;

		UPROPERTY(BlueprintReadOnly)
			bool firstAttack;

		UPROPERTY(BlueprintReadOnly)
			bool secondAttack;

		UPROPERTY(BlueprintReadOnly)
			bool thirdAttack;

		UPROPERTY(BlueprintReadOnly)
			bool fourthAttack;

		UPROPERTY(BlueprintReadOnly)
			bool firstHardAttack;

		UPROPERTY(BlueprintReadOnly)
			bool secondHardAttack;
#pragma endregion 

	
		void SetDirection(FVector2D d);

		void SetPlayerBlock(bool block);
		void SetPlayerNormalAttack(int attackNumber);
		void SetPlayerHardAttack(int hardAttackNumber);
		void SetPlayerDamage(int damageNumber);

		UFUNCTION(BlueprintCallable)
		void EndAttackEvent();

		UFUNCTION(BlueprintCallable)
		void StartAttackEvent();

		UFUNCTION(BlueprintCallable)
		void StartHardAttackEvent();

		UFUNCTION(BlueprintCallable)
		void DisableAttackCollider();

		UFUNCTION(BlueprintCallable)
		void DisableHardAttackCollider();

		UFUNCTION(BlueprintCallable)
		void DamageEndEvent();
	
};
