// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate signature
DECLARE_DYNAMIC_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAVAGETEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int maxLife;

	void BeginPlay();

	UPROPERTY();
	FOnDeathSignature OndeathDelegate;

	// Function signature
	void OnDeath();

	int life;

	class UHealthBarWidget* widget;


public:
	void TakeDamage(int amount);
	void Heal(int amount);
};
