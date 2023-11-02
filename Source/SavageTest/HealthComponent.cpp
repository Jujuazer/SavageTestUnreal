// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "HealthBarWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	life = maxLife;
}

void UHealthComponent::OnDeath()
{
	OndeathDelegate.Execute();
}


void UHealthComponent::TakeDamage(int amount)
{
	if (amount <= 0) {
		return;
	}

	life -= amount;

	if (life <= 0) 
	{
		OnDeath();
	}

	if (widget) {
		widget->UpdateHealth(life, maxLife);
	}
}

void UHealthComponent::Heal(int amount)
{
	if (amount <= 0) 
	{
		return;
	}

	life += amount;
	
	if (life > maxLife) 
	{
		life = maxLife;
	}
}




