// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
//#include "AOAPlayerCharecter.h"
#include "GameFramework/Character.h"
#include "ORBArean/widge/HealthBar.h"
#include "OrbAreanaEnemy.generated.h"

class UNiagaraSystem;
class AOAPlayerCharecter;

USTRUCT()
struct FEnemyState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,Category="|Health")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere,Category="|Health")
	float MaxHealth = 2000.0f;
	
	UPROPERTY(EditAnywhere,Category="|Speed")
	float BaseSpeed = 1200.f;
	
	UPROPERTY(EditAnywhere,Category="|Attack")
	float Damage = 1.f;
	UPROPERTY(EditAnywhere,Category="|Attack")
	float Range = 25.f;
	UPROPERTY(EditAnywhere,Category="|Attack")
	float AttackCooldown = 1.f;
};



UCLASS()
class ORBAREAN_API AOrbAreanaEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOrbAreanaEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(EditAnywhere,Category="Enemy|Info")
	FString EnemyName = "BasicEnemy";
	
	UPROPERTY(EditAnywhere,Category="Enemy|Stats")
	FEnemyState EnemyAttribut;
	
	UPROPERTY(EditAnywhere,Category="Enemy|Stats")
	AOAPlayerCharecter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere,Category="Enemy|Timer")
	float Timer = 0;
	

	/** Select your WBP_HealthBar here in the Editor */
	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* HealthWidgetComp;
 
	/** Reference to the instance so we can update it */
	UPROPERTY()
	UHealthBar* HealthBarInstance;
	
	
	// Enemy info
	FVector EnemyPos;
	
	// Ai Varibale
	UPROPERTY(EditAnywhere,Category="Enemy|AI", meta = (ClampMax=1.f,ClampMin=-1.f))
	float DotProduktSeePlayer =0.4;
	
	UPROPERTY(VisibleAnywhere,Category="Enemy|AI", meta = (ClampMax=1.f,ClampMin=-1.f))
	float DotPrukuktValue = 0.f;
	
	UPROPERTY(VisibleAnywhere,Category="Enemy|AI", meta = (ClampMax=1.f,ClampMin=-1.f))
	float CrossProdokkSide = 0.f;
	
	UPROPERTY(EditAnywhere,Category="Enemy|AI")
	float TresholdDotPrudukt = 0.99;
	
	UPROPERTY(VisibleAnywhere, Category="Enemy|AI")
	FVector CrossPrudoktValue = FVector(1.f,1.f,1.f);
	
	UPROPERTY(EditAnywhere,Category="Enemy|AI")
	float MaxVeiwingRange = 500;
	
	UPROPERTY(EditAnywhere,Category="Enemy|AI")
	bool bSeePlayer = false;
	
	UPROPERTY(EditAnywhere, Category="Enemy|AI")
	float TurnSpeed = 180.f;
	
	UPROPERTY(EditAnywhere,Category="Enemy|AI")
	bool bRequiedVisonToTurn = true;
	
	//SFX/VFX
	UPROPERTY(EditAnywhere,Category="Enemy|Feedback|VFX")
	UNiagaraSystem* TakeDamageVFX;
	
	UPROPERTY(EditAnywhere,Category="Enemy|Feedback|VFX")
	UNiagaraSystem* DeathVFX;
	
	UPROPERTY(EditAnywhere,Category="Enemy|FeedBack|SFX")
	USoundBase* DeathSFX;
	
	// Debug
	UPROPERTY(EditAnywhere,Category="Enemy|Debug")
	bool bDrawDebug = true;
	
	UPROPERTY(VisibleAnywhere, Category="Enemy|Debug")
	FColor DebugColor = {255,0,0};

	

	bool DealDamgeToPlayer(float DamgeAmount,FVector PlayerPos);
	void DamgeRecive(float DamgeAmount);
	void Heal(float HealAmount);
	void Move(FVector PlayerPos);
	
	// AI Funk
	void UpdateAI(float DeltaTime, FVector PlayerPo);
	
	// Debug Funk
	void PrintDebugValues();
	void DrawDebug();
	
	
};
