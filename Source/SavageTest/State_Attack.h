// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "State_Attack.generated.h"

class AEnemyBase;
class UHealthComponent;

UCLASS()
class SAVAGETEST_API UState_Attack : public UBaseState
{
	GENERATED_BODY()

	public :
		UState_Attack();

	private :
		AEnemyBase* owner;
	
	public :
		virtual void UpdateBehaviour(AEnemyBase*);
		virtual void StartBehaviour(AEnemyBase*);
		virtual void ExitBehaviour(AEnemyBase*);

		UHealthComponent* otherHealth;

		void Attack();

		UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
