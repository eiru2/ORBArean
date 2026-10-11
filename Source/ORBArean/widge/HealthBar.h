// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ORBAREAN_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable)
	void Update(float CurrentHealth, float MaxHealth);

	UPROPERTY( meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY( meta = (BindWidget))
	UTextBlock* CurrentHeatlhLabel;
	UPROPERTY( meta = (BindWidget))
	UTextBlock* MaxhealthLabel;
	

	
};
