// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OrbAreanHUDWidge.generated.h"

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
	UTextBlock* HealthTaxt;
	
	UPROPERTY( meta = (BindWidget))
	UTextBlock* ScoreText;
	
	

};
