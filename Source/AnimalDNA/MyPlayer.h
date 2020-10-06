
#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "MyUI.h"
#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExampleType, float, damage);
UCLASS()
class ANIMALDNA_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	AMyPlayer();

	int attackComboCount;
	int hardComboCount;

	UPROPERTY(EditAnywhere)
	float maxPlayerLife;
	UPROPERTY(VisibleAnywhere)
	float playerLife;

	float resetAttackTimer;
	float startToHeal;
	float healCoolDown;

	bool onBlock;
	bool dontMove;
	bool onAttack;
	bool canTakeDamage;
	bool dontAttack;
	bool startHeal;
	UPROPERTY(BlueprintReadOnly)
	bool playerIsDead;


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FExampleType OnDamage;


	UPROPERTY(BlueprintReadWrite)
	UBoxComponent * boxTrigger;
	UPROPERTY(BlueprintReadWrite)
	UBoxComponent * hardBoxTrigger;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* myKnife;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* mySecondKnife;

	UPROPERTY(VisibleAnywhere)
	UMaterial* myMaterialToLoad;
	USkeletalMeshComponent * myMesh;

	UMyAnimInstance* anim;

	FVector2D movementDirection;


protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveFront(float vertical);
	void MoveRight(float horizontal);
	void MovePlayer(FVector2D myDirection);

	void RotatePlayer(float rotation);
	void BlockAttacks();
	void UnBlockAttacks();

	void AttackCombo();
	void HardAttackCombo();

	void AttackResetComboCount(float deltaTimer);
	void PlayerHeal(float deltaTimer);

	UFUNCTION()
	void TakeDamage(float damage);
	
	void UpdatePlayerHUDLife();
	void PlayerDead();


	UFUNCTION(BlueprintCallable)
	void DamageEvent(float damageValue);

};
