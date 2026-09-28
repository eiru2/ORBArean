// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"
#include "OrbAreanEnergyOrb.generated.h"

UCLASS()
class ORBAREAN_API AOrbAreanEnergyOrb : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOrbAreanEnergyOrb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Orb attribute Variables
	
	UPROPERTY(EditAnywhere,Category="Config")
	float PickUpRadius = 50.0f;
	
	UPROPERTY(EditAnywhere,Category="Config")
	int32 OrbPointValue = 10;
	
	UPROPERTY(EditAnywhere,Category="Config")
	float Radius = 45.f;
	
	UPROPERTY(EditAnywhere,Category="Config")
	FColor Color = FColor(255,255,255,255); 
	
	UPROPERTY(EditAnywhere,Category="Config")
	FString OrbName = "rtyhj";
	
	bool IsPickedUp = false;
	UPROPERTY()
	ACharacter* PlayerCharacter;
	
	
	
	void OrbPickedUp(int32 InPointValue);
};
