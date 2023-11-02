// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemy.generated.h"

class AEnemyBase;

UCLASS()
class SAVAGETEST_API ASpawnEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* spawnBox;

	FBoxSphereBounds boxSizeBounds;

	FTimerHandle spawnTimerHandle;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyBase> toSpawn;

	void SpawnEnemy();
};
