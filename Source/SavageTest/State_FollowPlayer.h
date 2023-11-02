// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "State_FollowPlayer.generated.h"

class AEnemyBase;

UCLASS()
class SAVAGETEST_API UState_FollowPlayer : public UBaseState
{
	GENERATED_BODY()

	public :
		UState_FollowPlayer();

	private :
		AEnemyBase* owner;
	
	public :
		virtual void UpdateBehaviour(AEnemyBase*);
		virtual void StartBehaviour(AEnemyBase*);
		virtual void ExitBehaviour(AEnemyBase*);

		UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
