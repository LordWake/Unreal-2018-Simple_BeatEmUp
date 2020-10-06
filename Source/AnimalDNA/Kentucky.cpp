
#include "Kentucky.h"


AKentucky::AKentucky()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKentucky::BeginPlay()
{
	Super::BeginPlay();
	attackComboCount = 0;
	canTakeDamage = true;
	target = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto sk = FindComponentByClass<USkeletalMeshComponent>();
	if (sk)
		anim = Cast<UMyKentuckyAnimInstance>(sk->GetAnimInstance());

	if (normalBoxTrigger)
		normalBoxTrigger->SetGenerateOverlapEvents(false);
	if (hardBoxTrigger)
		hardBoxTrigger->SetGenerateOverlapEvents(false);
	
}

void AKentucky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckCurrentState(DeltaTime);
	ChangeState();
	ResetAttackCooldown(DeltaTime);
}

void AKentucky::TakeDamage(float damage)
{
	if (!canTakeDamage) return;
	bossLife = bossLife - damage;
	if (bossLife <= 0)
	{
		BossDead();
	}
	else if (bossLife > 0)
	{
		dontMove = true;
		dontAttack = true;
		canTakeDamage = false;
		float randomAnimation = FMath::RandRange(0, 2);
		if (anim)
			anim->SetBossDamage(randomAnimation);
	}
}

void AKentucky::BossDead()
{
	isDead = true;

	auto sk = FindComponentByClass<USkeletalMeshComponent>();
	if (sk)
		sk->SetCollisionProfileName(FName("NoCollision"));

	if (anim)
		anim->SetBossDead();

	auto canvas = Cast<AMyUI>(GetWorld()->GetFirstPlayerController());
	if (canvas)
		canvas->PlayerWins();
}

void AKentucky::CheckCurrentState(float deltaTime)
{
	if (!target || isDead) return;

	switch (current)
	{
		case EBehavioursBoss::Follow:
			FollowTarget(deltaTime);
			break;

		case EBehavioursBoss::LookPlayer:
		LookTarget();
		break;

		case EBehavioursBoss::Avoidance:
		AvoidObstacle(deltaTime);
		break;

		case EBehavioursBoss::AttackPlayer:
		AttackCombo();
		break;
	}
}

void AKentucky::LookTarget()
{
	if (isDead) return;

	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rotationVector = dir.Rotation();
	SetActorRotation(rotationVector);
}

void AKentucky::FollowTarget(float deltaTime)
{
	if (isDead || dontMove) return;

	LookTarget();
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTime);

	if (anim)
		anim->SetBossMovement(true);
}

void AKentucky::AvoidObstacle(float deltaTime)
{
	if (isDead || dontMove) return;

	if (!closestObstacle)
	{
		FollowTarget(deltaTime);
		return;
	}

	FVector direction = GetActorLocation() - closestObstacle->GetActorLocation();

	direction = (target->GetActorLocation() - GetActorLocation()).GetSafeNormal() + (direction.GetSafeNormal()*avoidWeight);

	direction.Z = 0;
	FVector rot = FMath::Lerp(GetActorForwardVector(), (direction), deltaTime*speedRot);

	SetActorRotation(rot.Rotation());
	SetActorLocation(GetActorLocation() + GetActorForwardVector()*speed*deltaTime);

}

void AKentucky::MyBeginOverlap(AActor* overlapActor)
{
	if (isDead) return;

	if (overlapActor == this || overlapActor == target)
		return;

	if (closestObstacle)
	{
		FVector distA = closestObstacle->GetActorLocation() - GetActorLocation();
		FVector distB = overlapActor->GetActorLocation() - GetActorLocation();

		if (distB.Size() < distA.Size())
			closestObstacle = overlapActor;

	}
	else
	{
		closestObstacle = overlapActor;
	}
}

void AKentucky::AttackCombo()
{
	if (isDead || dontAttack || waitToAttackAgain) return;
	
	float randomNumber = FMath::RandRange(0, 4); //Numero random para evaluar la posibilidad de que siga atacando o no en los ultimos tres ataques.

	if (anim)
		anim->SetBossMovement(false);

	dontMove = true;
	dontAttack = true;

	switch (attackComboCount)
	{
	case  0:
		if (anim)
			anim->SetBossAttack(attackComboCount);

		attackComboCount++;
		LookTarget();

		break;

	case 1:
		if (anim)
			anim->SetBossAttack(attackComboCount);

		attackComboCount++;
		LookTarget();
		break;

	case 2:
		if (anim)
			anim->SetBossAttack(attackComboCount);

		attackComboCount++;
		LookTarget();

		if (randomNumber == 2)
			waitToAttackAgain = true;
		break;

	case 3:
		if (anim)
			anim->SetBossAttack(attackComboCount);

		attackComboCount++;
		LookTarget();

		if (randomNumber == 2)
			waitToAttackAgain = true;
		break;

	case 4:
		if (anim)
			anim->SetBossAttack(attackComboCount);

		attackComboCount = 0;
		LookTarget();

		waitToAttackAgain = true;
		break;
	}
}

void AKentucky::ChangeState()
{
	if (isDead) return;

	if (distanceToPlayer <= 445.0f && distanceToPlayer >= 140.0f)
	{
		current = EBehavioursBoss::Avoidance;
	}
	else if (distanceToPlayer < 140.0f)
	{
		if (anim)
			anim->SetBossMovement(false);

		current = EBehavioursBoss::AttackPlayer;
	}
}

void AKentucky::ResetAttackCooldown(float deltaTime)
{
	if (waitToAttackAgain)
	{
		if (anim)
			anim->SetBossMovement(false);

		attackCooldown += deltaTime;
		dontMove = true;
		if (attackCooldown > 2.5f)
		{
			dontMove = false;
			attackCooldown = 0;
			waitToAttackAgain = false;
		}

	}
}

