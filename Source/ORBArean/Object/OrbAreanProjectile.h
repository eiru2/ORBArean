// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbAreanProjectile.generated.h"

class USphereComponent;

class UProjectileMovementComponent;

UCLASS()
class ORBAREAN_API AOrbAreanProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOrbAreanProjectile();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Component
	UPROPERTY(EditAnywhere,Category= "Projectile|Componet")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere,Category= "Projectile|Componet")
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere,Category= "Projectile|Componet")
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	//Damge
	UFUNCTION()
	void DamageEnemy(AActor* ThisAcoter, AActor* OtherActor);
	
	// State
	UPROPERTY(EditAnywhere, Category="Projectile|State")
	float DamageValue = 100.f;
	
	UPROPERTY(EditAnywhere, Category="Projectile|State")
	float LifeSpan = 1;
	
	
	//Debug
};

