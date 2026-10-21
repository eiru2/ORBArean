// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "OrbAreanEndScreenWidge.generated.h"


class UButton;

UCLASS()
class ORBAREAN_API UOrbAreanEndScreenWidge : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ResultText;
	
	// UPROPERTY( meta = (BindWidget))
	// UTextBlock* ScoreText;
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION()
	void RestartGame();
	
	UPROPERTY( meta = (BindWidget))
	UButton* RestartButton;
	
};
