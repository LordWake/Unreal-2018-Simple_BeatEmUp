#include "MyAnimInstance.h"
#include "MyPlayer.h"

void UMyAnimInstance::SetDirection(FVector2D d)
{
	playerDirection = d;
}

void UMyAnimInstance::SetPlayerBlock(bool blockState)
{
	playerIsBlocking = blockState;
}

void UMyAnimInstance::SetPlayerNormalAttack(int attackNumber)
{
	switch (attackNumber)
	{
		case  0:
			playerIsNotAttacking = false;
			firstAttack = true;
			break;

		case  1:
			playerIsNotAttacking = false;
			secondAttack = true;
			break;
	
		case  2:
			playerIsNotAttacking = false;
			thirdAttack = true;
			break;

		case  3:
			playerIsNotAttacking = false;
			fourthAttack = true;
			break;
	}
}

void UMyAnimInstance::SetPlayerHardAttack(int hardAttackNumber)
{
	switch (hardAttackNumber)
	{
	case  0:
		playerIsNotAttacking = false;
		firstHardAttack = true;
		break;

	case  1:
		playerIsNotAttacking = false;
		secondHardAttack = true;
		break;
	}
}

void UMyAnimInstance::EndAttackEvent()
{
	playerIsNotAttacking = true; //Avisamos que no estamos atacando para que sea el golpe que sea, vuelva al walkBlend.
	
								 //Tambien pasamos a falso todos los estados para que walkBlend no intente volver a ellos. El Player los vuelve a activar solo cuando lo necesite.
	firstAttack = false;
	secondAttack = false;
	thirdAttack = false;
	fourthAttack = false;
	firstHardAttack = false;
	secondHardAttack = false;
	

	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->dontMove = false;
		player->onAttack = false;
		player->canTakeDamage = true;
		player->myKnife->SetVisibility(false);
		player->mySecondKnife->SetVisibility(false);
	}
}

void UMyAnimInstance::StartAttackEvent()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->canTakeDamage = false; //No recibe daño mientras ataca.
		player->boxTrigger->SetGenerateOverlapEvents(true);
	}

}

void UMyAnimInstance::StartHardAttackEvent()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->canTakeDamage = false; 
		player->hardBoxTrigger->SetGenerateOverlapEvents(true);
	}
}

void UMyAnimInstance::DisableAttackCollider()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->boxTrigger->SetGenerateOverlapEvents(false);
	}
}

void UMyAnimInstance::DisableHardAttackCollider()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->hardBoxTrigger->SetGenerateOverlapEvents(false);
	}
}

void UMyAnimInstance::SetPlayerDamage(int damageNumber)
{
	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->canTakeDamage = false;
	}
	
	//Intercambio las distintas animaciones mediante un random que me envia el player.
	switch (damageNumber)
	{
		case 0:
			firstDamage = true;
			onDamageFinish = false;
			break;

		case  1:
			secondDamage = true;
			onDamageFinish = false;
			break;

		case 2:
			thirdDamage = true;
			onDamageFinish = false;
			break;
	}
}

void UMyAnimInstance::DamageEndEvent()
{
	onDamageFinish = true;
	firstDamage = false;
	secondDamage = false;
	thirdDamage = false;

	AMyPlayer* player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->canTakeDamage = true;
		player->dontAttack = false;
		player->dontMove = false;
	}
}