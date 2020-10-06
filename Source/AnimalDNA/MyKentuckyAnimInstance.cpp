// Fill out your copyright notice in the Description page of Project Settings.

#include "MyKentuckyAnimInstance.h"
#include "Kentucky.h"


void UMyKentuckyAnimInstance::SetBossMovement(bool movement)
{
	isMoving = movement;
}

void UMyKentuckyAnimInstance::SetBossDamage(int damagenumber)
{
	AKentucky * boss = Cast<AKentucky>(GetOwningActor());

	if (boss)
	{
		boss->canTakeDamage = false;
	}

	switch (damagenumber)
	{
	case 0:
		firstDamageAnimation = true;
		break;

	case  1:
		secondDamageAnimation = true;
		break;

	case  2:
		thirdDamageAnimation = true;
		break;
	}
}

void UMyKentuckyAnimInstance::OnBossDamageFinish()
{
	firstDamageAnimation = false;
	secondDamageAnimation = false;
	thirdDamageAnimation = false;

	AKentucky* boss = Cast<AKentucky>(GetOwningActor());
	if (boss)
	{
		boss->dontMove = false;
		boss->canTakeDamage = true;
		boss->dontAttack = false;
	}
}

void UMyKentuckyAnimInstance::SetBossDead()
{
	bossIsDead = true;
}

void UMyKentuckyAnimInstance::SetBossAttack(int attackNumber)
{
	switch (attackNumber)
	{
	case  0:
		bossIsNotAttacking = false;
		firstAttack = true;
		break;

	case  1:
		bossIsNotAttacking = false;
		secondAttack = true;
		break;

	case  2:
		bossIsNotAttacking = false;
		thirdAttack = true;
		break;

	case  3:
		bossIsNotAttacking = false;
		specialOne = true;
		break;

	case  4:
		bossIsNotAttacking = false;
		specialTwo = true;
		break;
	}
}

void UMyKentuckyAnimInstance::StartAttackEvent()
{
	AKentucky* boss = Cast<AKentucky>(GetOwningActor());
	if (boss)
	{
		boss->canTakeDamage = false;
		boss->normalBoxTrigger->SetGenerateOverlapEvents(true);
	}
}

void UMyKentuckyAnimInstance::StartHardAttackEvent()
{
	AKentucky* boss = Cast<AKentucky>(GetOwningActor());
	if (boss)
	{
		boss->canTakeDamage = false;
		boss->hardBoxTrigger->SetGenerateOverlapEvents(true);
	}
}

void UMyKentuckyAnimInstance::DisableAttackCollider()
{
	AKentucky* boss = Cast<AKentucky>(GetOwningActor());
	if (boss)
	{
		boss->normalBoxTrigger->SetGenerateOverlapEvents(false);
		boss->hardBoxTrigger->SetGenerateOverlapEvents(false);
	}
}

void UMyKentuckyAnimInstance::EndAttackEvent()
{
	bossIsNotAttacking = true;
	firstAttack = false;
	secondAttack = false;
	thirdAttack = false;
	specialOne = false;
	specialTwo = false;

	AKentucky* boss = Cast<AKentucky>(GetOwningActor());
	if (boss)
	{
		boss->canTakeDamage = true;
		boss->dontMove = false;
		boss->dontAttack = false;
	}
}


