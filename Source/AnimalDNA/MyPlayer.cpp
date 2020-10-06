#include "MyPlayer.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	auto materialObject = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/3DModels/Player/Materials/PlayerMaterial.PlayerMaterial'"));
	if (materialObject.Object)
		myMaterialToLoad = materialObject.Object;
}


void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	playerLife = maxPlayerLife;
	attackComboCount = 0;
	hardComboCount = 0;
	canTakeDamage = true;

	OnDamage.AddDynamic(this, &AMyPlayer::TakeDamage);
	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	
	if (myMesh && myMaterialToLoad)
		myMesh->SetMaterial(0, myMaterialToLoad);
	if (myMesh)
		anim = Cast<UMyAnimInstance>(myMesh->GetAnimInstance());
	if (boxTrigger)
		boxTrigger->SetGenerateOverlapEvents(false);
	if (hardBoxTrigger)
		hardBoxTrigger->SetGenerateOverlapEvents(false);
	if (myKnife)
		myKnife->SetVisibility(false);
	if (mySecondKnife)
		mySecondKnife->SetVisibility(false);

}


void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer(movementDirection);
	AttackResetComboCount(DeltaTime);
	PlayerHeal(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyPlayer::MoveFront);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Rotate", this, &AMyPlayer::RotatePlayer);

	PlayerInputComponent->BindAction("LB", IE_Pressed, this, &AMyPlayer::BlockAttacks);
	PlayerInputComponent->BindAction("LB", IE_Released, this, &AMyPlayer::UnBlockAttacks);
	PlayerInputComponent->BindAction("XButton", IE_Pressed, this, &AMyPlayer::AttackCombo);
	PlayerInputComponent->BindAction("YButton", IE_Pressed, this, &AMyPlayer::HardAttackCombo);
}

void AMyPlayer::MoveFront(float vertical)
{
	movementDirection.Y = vertical;
}

void AMyPlayer::MoveRight(float horizontal)
{
	movementDirection.X = horizontal;
}

void AMyPlayer::MovePlayer(FVector2D movementDirection)
{
	if (onBlock || dontMove || onAttack || playerIsDead || dontAttack) return;

	AddMovementInput(GetActorForwardVector(), movementDirection.Y);
	AddMovementInput(GetActorRightVector(), movementDirection.X);

	if (anim)
		anim->SetDirection(movementDirection);
}

void AMyPlayer::RotatePlayer(float rotation)
{
	if (playerIsDead || dontAttack) return;
	AddControllerYawInput(rotation);
}

void AMyPlayer::BlockAttacks()
{
	if (playerIsDead || onAttack || dontAttack) return;
	onBlock = true;
	if (anim)
		anim->SetPlayerBlock(onBlock);
}

void AMyPlayer::UnBlockAttacks()
{
	onBlock = false;
	if (anim)
		anim->SetPlayerBlock(onBlock);
}

void AMyPlayer::AttackCombo()
{
	if (onAttack || dontAttack || playerIsDead) return;

	switch (attackComboCount)
	{
	case 0:
		if (anim)
			anim->SetPlayerNormalAttack(attackComboCount);

		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		attackComboCount++;
		break;

	case  1:
		if (anim)
			anim->SetPlayerNormalAttack(attackComboCount);

		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		attackComboCount++;
		break;

	case  2:
		if (anim)
			anim->SetPlayerNormalAttack(attackComboCount);

		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		attackComboCount++;
		break;

	case  3:
		if (anim)
			anim->SetPlayerNormalAttack(attackComboCount);

		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		attackComboCount = 0;
		break;
	}
}

void AMyPlayer::HardAttackCombo()
{
	if (onAttack || dontAttack || playerIsDead) return;

	switch (hardComboCount)
	{
	case 0:
		if (anim)
			anim->SetPlayerHardAttack(hardComboCount);

		myKnife->SetVisibility(true);
		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		hardComboCount++;
		break;

	case  1:
		if (anim)
			anim->SetPlayerHardAttack(hardComboCount);

		mySecondKnife->SetVisibility(true);
		dontMove = true;
		onAttack = true;
		resetAttackTimer = 0;
		hardComboCount = 0;
		break;
	}
}

void AMyPlayer::AttackResetComboCount(float deltaTimer)
{
	resetAttackTimer += deltaTimer;
	if (resetAttackTimer > 3)
	{
		attackComboCount = 0;
		hardComboCount = 0;
	}
}

void AMyPlayer::TakeDamage(float damage)
{
	if (onBlock || playerIsDead || onAttack || !canTakeDamage) return;

	startHeal = true;
	startToHeal = 0;
	healCoolDown = 0;

	playerLife = playerLife - damage;
	dontAttack = true;
	UpdatePlayerHUDLife();
	if (playerLife <= 0)
	{
		PlayerDead();
	}
	else if(playerLife > 0)
	{
		dontMove = true;
		float randomAnimation = FMath::RandRange(0, 2);
		if (anim)
			anim->SetPlayerDamage(randomAnimation);
	}
}

void AMyPlayer::DamageEvent(float damageValue)
{
	OnDamage.Broadcast(damageValue);
}

void AMyPlayer::UpdatePlayerHUDLife()
{
	auto life = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	float updateLifeValue = playerLife / maxPlayerLife;
	if (life)
		life->UpdatePlayerLife(updateLifeValue);
}

void AMyPlayer::PlayerHeal(float deltaTimer)
{
	if (!startHeal) return;

	startToHeal += deltaTimer;
	if (startToHeal > 5)
	{
		healCoolDown += deltaTimer;
		if (healCoolDown >= 1)
		{
			if (playerLife < maxPlayerLife)
			{
				playerLife++;
				UpdatePlayerHUDLife();
			}
			else
			{
				startHeal = false;
			}
			healCoolDown = 0;
		}
	}
}

void AMyPlayer::PlayerDead()
{
	playerIsDead = true;
	if (anim)
		anim->onPlayerDead = true;

	auto canvas = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	if (canvas)
		canvas->PlayerDead();
}







