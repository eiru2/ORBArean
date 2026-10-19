// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OrbAreanHUDWidge.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ORBAREAN_API UOrbAreanHUDWidge : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ReamingLifeText;
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* HealthTaxt;
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ReamingOrbs;
	
	UPROPERTY( meta = (BindWidget))
	UButton* RestartButton;
	
	UPROPERTY(EditAnywhere,Category="Color|Heatlth")
	FSlateColor HeatlhWarningColor = FColor(255,0,0);
	
	UPROPERTY(EditAnywhere,Category="Color|Heatlth")
	FSlateColor HealthColor = FColor(255,255,255);

	UFUNCTION()
	void RestartGame();
};
