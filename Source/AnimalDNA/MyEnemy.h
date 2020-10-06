#pragma once

#include "Engine.h"
#include "MyEnemyAnimInstance.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.generated.h"


UENUM(BlueprintType)
enum class EBehavioursEnemy :uint8
{
	Follow UMETA(DisplayName = "Follow Target"),
	LookPlayer UMETA(DisplayName = "Look Target"),
	Avoidance UMETA(DisplayName = "Avoidance"),
	AttackPlayer UMETA(DisplayName = "Attack Player"),
};

UCLASS()
class ANIMALDNA_API AMyEnemy : public AActor
{
	GENERATED_BODY()
	
public:	

	AMyEnemy();

	UPROPERTY(VisibleAnywhere)
	AActor* target;

	UPROPERTY(EditAnywhere, Category = Enum)
	EBehavioursEnemy current;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* boxTrigger;

	UPROPERTY(EditAnywhere)
	float speed;

	UPROPERTY(EditAnywhere)
	float speedRot;

	UPROPERTY(EditAnywhere)
	float avoidWeight;

	UPROPERTY(BlueprintReadWrite)
	float distanceToPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* closestObstacle;
	
	bool canTakeDamage;
	bool dontAttack;
	bool waitToAttackAgain;
	bool dontMove;
	bool isDead;
	bool startMyIA;

	int attackComboCount;
	float attackCooldown;

	UMyEnemyAnimInstance * anim;

	UPROPERTY(EditAnywhere)
	int enemyLife;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);
	
	void EnemyDead();

	void CheckCurrentState(float deltaTime);
	void FollowTarget(float deltaTime);
	void LookTarget();
	void AvoidObstacle(float deltaTime);
	void ChangeState();
	void ResetAttackCooldown(float deltaTime);

	void AttackCombo();

	UFUNCTION(BlueprintCallable)
	void MyBeginOverlap(AActor* overlapActor);
};
