// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
 

void UHealthBarWidget::UpdateHealth(int life, int maxlife)
{
	HealthBar->SetPercent(static_cast<float>(life) / maxlife);
	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	CurrentHealthLabel1->SetText(FText::AsNumber(life, &Opts));
	MaxHealthLabel->SetText(FText::AsNumber(maxlife, &Opts));
}
