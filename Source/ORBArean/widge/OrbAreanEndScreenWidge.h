// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "OrbAreanEndScreenWidge.generated.h"




UCLASS()
class ORBAREAN_API UOrbAreanEndScreenWidge : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ResultText;
	
	// UPROPERTY( meta = (BindWidget))
	// UTextBlock* ScoreText;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

};
