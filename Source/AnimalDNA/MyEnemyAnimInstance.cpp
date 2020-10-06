
#include "MyEnemyAnimInstance.h"
#include "MyEnemy.h"


void UMyEnemyAnimInstance::SetEnemyMovement(bool movement)
{
	isMoving = movement;
}

void UMyEnemyAnimInstance::SetEnemyDamage(int damageNumber)
{
	AMyEnemy* enemy = Cast<AMyEnemy>(GetOwningActor());

	if (enemy)
	{
		enemy->canTakeDamage = false;
	}

		switch (damageNumber)
		{
			case 0:
				firstDamageAnimation = true;
				break;

			case 1:
				secondDamageAnimation = true;
				break;
		}
}

void UMyEnemyAnimInstance::OnDamageFinish()
{
	firstDamageAnimation = false;
	secondDamageAnimation = false;
	
	AMyEnemy* enemy = Cast<AMyEnemy>(GetOwningActor());
	if(enemy)
	{
		enemy->dontMove = false;
		enemy->canTakeDamage = true;
		enemy->dontAttack = false;	
	}
}

void UMyEnemyAnimInstance::SetEnemyDead()
{
	enemyIsDead = true;
}

void UMyEnemyAnimInstance::SetEnemyAttack(int attackNumber)
{
	switch (attackNumber)
	{
	case  0:
		enemyIsNotAttackin = false;
		firstAttack = true;
		break;

	case  1:
		enemyIsNotAttackin = false;
		secondAttack = true;
		break;

	case  2:
		enemyIsNotAttackin = false;
		thirdAttack = true;
		break;
	}
}

void UMyEnemyAnimInstance::EndAttackEvent()
{
	enemyIsNotAttackin = true;
	firstAttack = false;
	secondAttack = false;
	thirdAttack = false;

	AMyEnemy* enemy = Cast<AMyEnemy>(GetOwningActor());
	if (enemy)
	{
		enemy->canTakeDamage = true;
		enemy->dontMove = false;
		enemy->dontAttack = false;
	}
}

void UMyEnemyAnimInstance::StartAttackEvent()
{
	AMyEnemy* enemy = Cast<AMyEnemy>(GetOwningActor());
	if (enemy)
	{
		enemy->canTakeDamage = false;
		enemy->boxTrigger->SetGenerateOverlapEvents(true);
	}
}

void UMyEnemyAnimInstance::DisableAttackCollider()
{
	AMyEnemy* enemy = Cast<AMyEnemy>(GetOwningActor());
	if (enemy)
	{
		enemy->boxTrigger->SetGenerateOverlapEvents(false);
	}
}



