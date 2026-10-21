// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanEndScreenWidge.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"


void UOrbAreanEndScreenWidge::NativeConstruct()
{
	Super::NativeConstruct();
	RestartButton->OnClicked.AddDynamic(this,&UOrbAreanEndScreenWidge::RestartGame);
	
}

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

void UOrbAreanEndScreenWidge::RestartGame()
{
	UE_LOG(LogTemp,Warning,TEXT("Rest"))
	UGameplayStatics::OpenLevel(GetWorld(),"BaseGameMode");
}
