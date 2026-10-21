// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBar.generated.h"

USTRUCT()
struct FNumberDisplay
{
	GENERATED_BODY()
	float Value;
	FString Symbol;
};

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
	
	// Ai to fast finshed
	UPROPERTY(EditAnywhere,Category="Color|Heatlth")
	TArray<FNumberDisplay> DisplayNumber = {
		{ 1,  ""  },
		{ 1e3,  "k"  }, // Tusen
		{ 1e6,  "M"  }, // Million
		{ 1e9,  "B"  }, // Milliard (Billion på engelsk)
		{ 1e12, "T"  }, // Billion (Trillion på engelsk)
		{ 1e15, "Qa" }, // Quadrillion
		{ 1e18, "Qi" }  // Quintillion
	};
	
};
