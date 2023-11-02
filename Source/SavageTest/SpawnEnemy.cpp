// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemy.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.h"

// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// create box and set it to not have physics
	spawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	spawnBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	spawnBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	boxSizeBounds = spawnBox->CalcBounds(GetActorTransform());

	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &ASpawnEnemy::SpawnEnemy, 2, true);
}

void ASpawnEnemy::SpawnEnemy()
{
	FVector spawnLocation = boxSizeBounds.Origin;
	spawnLocation.X += -boxSizeBounds.BoxExtent.X + 2 * boxSizeBounds.BoxExtent.X * FMath::FRand();
	spawnLocation.Y += -boxSizeBounds.BoxExtent.Y + 2 * boxSizeBounds.BoxExtent.Y * FMath::FRand();
	spawnLocation.Z += -boxSizeBounds.BoxExtent.Z + 2 * boxSizeBounds.BoxExtent.Z * FMath::FRand();
	GetWorld()->SpawnActor(toSpawn, &spawnLocation);
}


