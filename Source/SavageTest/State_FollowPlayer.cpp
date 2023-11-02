// Fill out your copyright notice in the Description page of Project Settings.


#include "State_FollowPlayer.h"
#include "EnemyBase.h"
#include "CharacterTopDown.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AIEnemyController.h"
#include "State_Attack.h"
#include "Components/BoxComponent.h"

UState_FollowPlayer::UState_FollowPlayer()
{
}

void UState_FollowPlayer::UpdateBehaviour(AEnemyBase* entity)
{
	FVector playerPosition = entity->player->GetPawn()->GetActorLocation();
	if (entity->AIcontrol) 
	{
		entity->AIcontrol->MoveToLocation(playerPosition, 1, true, false);
	}
}

void UState_FollowPlayer::StartBehaviour(AEnemyBase* entity)
{
	owner = entity;

	//debug ces deux qui causent un crash lorsque l'on va sur ce state
	entity->boxCollider->OnComponentBeginOverlap.AddDynamic(this, &UState_FollowPlayer::OnOverlapBegin);
}

void UState_FollowPlayer::ExitBehaviour(AEnemyBase* entity)
{
	entity->AIcontrol->MoveToLocation(entity->GetActorLocation());
}

void UState_FollowPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacterTopDown>(OtherActor)) {
		owner->boxCollider->OnComponentBeginOverlap.Clear();
		owner->ChangeState(owner->attackState);
		owner->attackState->OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

