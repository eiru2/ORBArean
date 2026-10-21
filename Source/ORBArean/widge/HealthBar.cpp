// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"


void UHealthBar::Update(float CurrentHealth, float MaxHealth)
{
	if (CurrentHealth != 0)
	{
		HealthBar->SetPercent(CurrentHealth/MaxHealth);
	}
	FText HealthSting;
	FText MaxHealthSting;
	for (FNumberDisplay Number : DisplayNumber)
	{
		if (CurrentHealth/Number.Value < 1){break;}
		float tempValue = FMath::RoundToInt((CurrentHealth/Number.Value)*10.f)/10.f;
		HealthSting = FText::FromString(FString::Printf(TEXT("%s%s"),*FString::SanitizeFloat(tempValue), *Number.Symbol));
	}
	for (FNumberDisplay Number : DisplayNumber)
	{
		if (MaxHealth/Number.Value < 1){break;}
		float tempValue = FMath::RoundToInt((MaxHealth/Number.Value)*10.f)/10.f;
		MaxHealthSting = FText::FromString(FString::Printf(TEXT("%s%s"),*FString::SanitizeFloat(tempValue), *Number.Symbol));
	}
	CurrentHeatlhLabel->SetText(HealthSting);
	
	MaxhealthLabel->SetText(MaxHealthSting);
	
}
