// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthComponent.h"
#include "HealthBarWidget.generated.h"


UCLASS( Abstract )
class SAVAGETEST_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void SetOwner(UHealthComponent* component) { healthComponent = component; }

	void UpdateHealth(int life, int maxlife);

protected:

	TWeakObjectPtr<UHealthComponent> healthComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthLabel1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealthLabel;

};
