// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanHUDWidge.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"

void UOrbAreanHUDWidge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	AOAPlayerCharecter* Player = Cast<AOAPlayerCharecter>(GetOwningPlayerPawn());
	
	if (not IsValid(Player))
	{
		return;
	}
	if (Player->PlayerAttribute.Health <= Player->PlayerAttribute.LowHeatlhThrseold*Player->PlayerAttribute.MaxHealth)
	{	
		HealthTaxt->SetColorAndOpacity(HeatlhWarningColor);
	}
	else{HealthTaxt->SetColorAndOpacity(HealthColor);}
	
	
	HealthTaxt->SetText(FText::FromString(FString::Printf(TEXT("Health: %.0f"), Player->PlayerAttribute.Health)));
	ReamingLifeText->SetText(FText::FromString(FString::Printf(TEXT("Life %i"),Player->PlayerAttribute.Life)));
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score %i"),Player->Score)));
	ReamingOrbs->SetText(FText::FromString(FString::Printf(TEXT("Remining Orbs, %i"),Player->AmountOfOrbsLeft)));
	

}

