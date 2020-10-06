#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "MyUI.h"
#include "MyKentuckyAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Kentucky.generated.h"

UENUM(BlueprintType)
enum class EBehavioursBoss :uint8
{
	Follow UMETA(DisplayName = "Follow Target"),
	LookPlayer UMETA(DisplayName = "Look Target"),
	Avoidance UMETA(DisplayName = "Avoidance"),
	AttackPlayer UMETA(DisplayName = "Attack Player"),
};

UCLASS()
class ANIMALDNA_API AKentucky : public AActor
{
	GENERATED_BODY()
	
public:	

	AKentucky();

	UPROPERTY(VisibleAnywhere)
	AActor* target;

	UPROPERTY(EditAnywhere, Category = Enum)
	EBehavioursBoss current;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* normalBoxTrigger;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* hardBoxTrigger;

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

	int attackComboCount;
	float attackCooldown;

	UMyKentuckyAnimInstance * anim;

	UPROPERTY(EditAnywhere)
	int bossLife;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);

	void BossDead();

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
