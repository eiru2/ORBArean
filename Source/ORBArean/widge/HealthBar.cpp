// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"


void UHealthBar::Update(float CurrentHealth, float MaxHealth)
{
	if (CurrentHealth != 0)
	{
		HealthBar->SetPercent(CurrentHealth/MaxHealth);
	}

	CurrentHeatlhLabel->SetText(FText::AsNumber(CurrentHealth));
	
	MaxhealthLabel->SetText(FText::AsNumber(MaxHealth));
	
}
