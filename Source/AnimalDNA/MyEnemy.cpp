#include "MyEnemy.h"



AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	canTakeDamage = true;
	target = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto sk = FindComponentByClass<USkeletalMeshComponent>();
	if (sk)
		anim = Cast<UMyEnemyAnimInstance>(sk->GetAnimInstance());

	if (boxTrigger)
		boxTrigger->SetGenerateOverlapEvents(false);
}


void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckCurrentState(DeltaTime);
	ChangeState();
	ResetAttackCooldown(DeltaTime);
}

void AMyEnemy::TakeDamage(float damage)
{	
	if (!canTakeDamage) return;

	enemyLife = enemyLife - damage;
	if (enemyLife <= 0)
	{
		EnemyDead();
	}

	else if(enemyLife > 0)
	{
		dontMove = true;
		dontAttack = true;
		canTakeDamage = false;
		float randomAnimation = FMath::RandRange(0, 1);
		if (anim)
			anim->SetEnemyDamage(randomAnimation);
	}
}

void AMyEnemy::EnemyDead()
{
	isDead = true;

	auto sk = FindComponentByClass<USkeletalMeshComponent>();
	if (sk)
		sk->SetCollisionProfileName(FName("NoCollision"));

	if (anim)
		anim->SetEnemyDead();

}

void AMyEnemy::CheckCurrentState(float deltaTime)
{
	if (!target || isDead || !startMyIA) return;

	switch (current)
	{
		case EBehavioursEnemy::Follow:
		FollowTarget(deltaTime);
		break;

		case EBehavioursEnemy::LookPlayer:
		LookTarget();
		break;

		case EBehavioursEnemy::Avoidance:
		AvoidObstacle(deltaTime);
		break;

		case  EBehavioursEnemy::AttackPlayer:
		AttackCombo();
		break;
	}
}

void AMyEnemy::LookTarget()
{
	if (isDead) return;

	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rotationVector = dir.Rotation();
	SetActorRotation(rotationVector);
}

void AMyEnemy::FollowTarget(float deltaTime)
{
	if (isDead || dontMove) return;

	LookTarget();
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTime);
	
	if (anim)
		anim->SetEnemyMovement(true);
}

void AMyEnemy::AvoidObstacle(float deltaTime)
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

void AMyEnemy::MyBeginOverlap(AActor* overlapActor)
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

void AMyEnemy::AttackCombo()
{
	if (isDead || dontAttack || waitToAttackAgain) return;

	if (anim)
		anim->SetEnemyMovement(false);

	dontMove = true; 
	dontAttack = true;

	switch (attackComboCount)
	{
		case  0:
			if (anim)
				anim->SetEnemyAttack(attackComboCount);
				attackComboCount++;
				LookTarget();
		break;

	case 1:
		if (anim)
			anim->SetEnemyAttack(attackComboCount);
			attackComboCount++;
			LookTarget();
		break;

	case 2:
			if (anim)
			anim->SetEnemyAttack(attackComboCount);
			attackComboCount = 0;
			LookTarget();

			waitToAttackAgain = true;		
		break;
	}
}

void AMyEnemy::ChangeState()
{
	if (isDead) return;
	
	if (distanceToPlayer <= 445.0f && distanceToPlayer >= 140.0f)
	{
		startMyIA = true;
		current = EBehavioursEnemy::Avoidance;
	}
	else if (distanceToPlayer < 140.0f)
	{
		startMyIA = true;
		if (anim)
			anim->SetEnemyMovement(false);

		current = EBehavioursEnemy::AttackPlayer;
	}
}

void AMyEnemy::ResetAttackCooldown(float deltaTime)
{
	if (waitToAttackAgain) 
	{
		if (anim)
			anim->SetEnemyMovement(false);

		attackCooldown += deltaTime;
		dontMove = true;
		if (attackCooldown > 5)
		{
			dontMove = false;
			attackCooldown = 0;
			waitToAttackAgain = false;
		}
	
	}

}


