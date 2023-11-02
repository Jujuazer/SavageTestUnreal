// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UBaseState;
class AAIController;
class UState_FollowPlayer;
class UState_Attack;
class AAIEnemyController;
class UBoxComponent;
class UHealthComponent;


UCLASS()
class SAVAGETEST_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// current state used by tick and when changing state
	UPROPERTY()
	UBaseState* actualState;

	// states
	UPROPERTY()
	UState_FollowPlayer* followState;
	UPROPERTY()
	UState_Attack* attackState;


	// runtime refs
	UHealthComponent* healthComponent;
	APlayerController* player;
	UPROPERTY()
	AAIEnemyController* AIcontrol;
	UCapsuleComponent* capsuleCollider;
	UBoxComponent* boxCollider;
	
	// timer handle for attack delay
	FTimerHandle attackTimeHandle;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int attackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int damage;


	void ChangeState(UBaseState* to);

	// ondeath after timing call die to destroy the actor
	void Die();

	// bind to health component
	UFUNCTION()
	void OnDeath();

	// when colliding print TOUCH
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:
	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
