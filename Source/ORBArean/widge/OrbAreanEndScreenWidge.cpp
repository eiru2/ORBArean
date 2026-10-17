// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanEndScreenWidge.h"

#include "Components/TextBlock.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"


void UOrbAreanEndScreenWidge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	AOAPlayerCharecter* Player = Cast<AOAPlayerCharecter>(GetOwningPlayerPawn());
	
	if (not IsValid(Player))
	{
		return;
	}
	if (Player->GameState == EGameState::Won)
	{
		ResultText->SetText(FText::FromString(FString("YOU Won")));
	}
	if (Player->GameState == EGameState::Lost)
	{
		ResultText->SetText(FText::FromString(FString("YOU Lost")));
	}
}
