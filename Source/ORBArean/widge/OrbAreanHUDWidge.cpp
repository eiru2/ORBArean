// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanHUDWidge.h"

#include "Components/TextBlock.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"

void UOrbAreanHUDWidge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	AOAPlayerCharecter* Player = Cast<AOAPlayerCharecter>(GetOwningPlayerPawn());
	
	if (not IsValid(Player))
	{
		return;
	}
	HealthTaxt->SetText(FText::FromString(FString::Printf(TEXT("Health: %.0f"), Player->PlayerAttribute.Health)));
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score %i"),Player->Score)));
}
