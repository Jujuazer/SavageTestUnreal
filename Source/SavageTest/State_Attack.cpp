// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Attack.h"
#include "EnemyBase.h"
#include "Components/BoxComponent.h"
#include "State_FollowPlayer.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.h"

UState_Attack::UState_Attack()
{
}

void UState_Attack::UpdateBehaviour(AEnemyBase* entity)
{

}

void UState_Attack::StartBehaviour(AEnemyBase* entity)
{
	owner = entity;
	//debug ces deux qui causent un crash lorsque l'on va sur ce state
	entity->boxCollider->OnComponentEndOverlap.AddDynamic(this, &UState_Attack::OnOverlapEnd);

	GetWorld()->GetTimerManager().SetTimer(entity->attackTimeHandle, this, &UState_Attack::Attack, entity->attackSpeed, true);
}

void UState_Attack::ExitBehaviour(AEnemyBase* entity)
{
	entity->boxCollider->OnComponentEndOverlap.Clear();
	GetWorld()->GetTimerManager().ClearTimer(entity->attackTimeHandle);
}

void UState_Attack::Attack()
{
	if (otherHealth && owner)
	{
		otherHealth->TakeDamage(owner->damage);
	}
}

void UState_Attack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	otherHealth = OtherActor->GetComponentByClass<UHealthComponent>();
}

void UState_Attack::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	owner->ChangeState(owner->followState);
}