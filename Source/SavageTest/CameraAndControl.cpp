// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraAndControl.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACameraAndControl::ACameraAndControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraAndControl::BeginPlay()
{
	Super::BeginPlay();
	pawnPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ACameraAndControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector vectPosition = FVector(pawnPlayer->GetActorLocation().X, pawnPlayer->GetActorLocation().Y, 460);

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	SetActorLocation(vectPosition);
}

