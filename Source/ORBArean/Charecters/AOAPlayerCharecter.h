// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ORBArean/Object/OrbAreanEnergyOrb.h"
//#include "../../../../../../../Program Files/Epic Games/UE_5.8/Engine/Plugins/Media/AjaMedia/Source/AjaMedia/Private/Shared/AjaMediaAllowPlatformTypes.h"
#include "Splines/SplineMath.h"
#include "EnhancedInputSubsystems.h"
#include "AOAPlayerCharecter.generated.h"

USTRUCT(meta=(DisableSplitPin))
struct FCharecterState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,Category="Health")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere,Category="Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere,Category="Health")
	int32 Life = 3;
	UPROPERTY(EditAnywhere,Category="Health")
	int32 MaxLife = 3;
	
	UPROPERTY(EditAnywhere,Category="Speed")
	float BaseSpeed = 1200;
	
	UPROPERTY(EditAnywhere,Category="Damage")
	float Damage = 10;
};

USTRUCT()
struct FEnemyState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,Category="Ennemy|Stats|Health")
	float Health = 200.0f;
	UPROPERTY(EditAnywhere,Category="Ennemy|Stats|Health")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere,Category="Ennemy|Stats|Speed")
	float BaseSpeed = 1200;
	
	UPROPERTY(EditAnywhere,Category="Ennemy|Stats|Speed")
	float Damage = 10;
};


UENUM()
enum class EGameState : uint8
{
	Playing,
	Won,
	Lost
};

/*
 * Advance Task
 */
UENUM()
enum class EGameDifficulty : uint8
{
	Easy,
	Medium,
	Hard,
	Test
};
// FLootDrop



USTRUCT()
struct FLootDrop
{
	GENERATED_BODY()
	FString Name;
	float Value;
	enum ERarity
	{
		Common,
		Uncommon,
		Rare,
		SuperRare,
		UberRare,
		Legndery,
	};
	ERarity Rarity;
	TArray<FString> RartyLabel = {	"Common","Uncommon","Rare","SuperRare","UberRare","Legndery",};
};


UCLASS()
class ORBAREAN_API AOAPlayerCharecter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOAPlayerCharecter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(EditAnywhere,Category="Player")
	FCharecterState PlayerAttribute;
	
	FEnemyState Enemy;
	
	UPROPERTY(EditAnywhere, Category = "Loot")
	TArray<FLootDrop> ArrayLootDrop = {
		FLootDrop("RustySword", 10, FLootDrop::Common),
		FLootDrop ("Sword", 25, FLootDrop::Rare),
		FLootDrop ("HeroSword", 50, FLootDrop::Legndery),
		FLootDrop ("LoveSword", 99999, FLootDrop::Legndery),
	};
	
	//void AddScore(int32 InAmount);
	//void HealPlayer(float InAmount);
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
		
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* SprintAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* HealAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* HealActionMax;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* DamageAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* AddScoreAction;
	

	UPROPERTY(EditAnywhere,Category="Player|Stats|Health")
	float TempHeal = 10.0f;
	UPROPERTY(EditAnywhere,Category="Player|Stats|Health")
	float HealthWarningThreshold = 20.f;
	bool LowHealthFlag = false;
	float TempDamge = 10.f;
	
	UPROPERTY(EditAnywhere,Category="Player|Stats|Speed")
	float CurrentMovmentSpeed = PlayerAttribute.BaseSpeed;
	// Easy, Medium Harde
	UPROPERTY(EditAnywhere,Category="Player|Stats|Speed")
	// Can break if there is duplicate keys
	TMap<EGameDifficulty, float> DifficultySpeedMultiplier;

	
	UPROPERTY(EditAnywhere,Category="Player|Stats|Speed")
	float SprintMultiplier = 2.f;
	UPROPERTY(EditAnywhere,Category="Player|Stats|Speed")
	bool Sprinting = false;
	UPROPERTY(EditAnywhere,Category="Player|Stats|Speed")
	float Acceleration = CurrentMovmentSpeed*2;
	
	UPROPERTY(EditAnywhere,Category="Player|Stats")
	FString PlayerPos = "{0,0,0}";
	FVector MoveCharecterThisFrame;
	
	UPROPERTY(EditAnywhere,Category="Player|Info")
	int32 Score = 0;
	int32 TempScore = 2;
	
	UPROPERTY(EditAnywhere,Category="Player|Info")
	int32 Level = 42;
	
	UPROPERTY(EditAnywhere,Category="Player|Info")
	FString Name = "Tor ";
	
	UPROPERTY(EditAnywhere,Category="Game|Info")
	int64 ScoreWinCondition = 200000000000;
	
	UPROPERTY(EditAnywhere,Category="Game|Info")
	EGameState GameState = EGameState::Playing;
	
	UPROPERTY(EditAnywhere,Category="Game|Info")
	EGameDifficulty GameDifficulty = EGameDifficulty::Easy;
	


	
	TArray<AOrbAreanEnergyOrb*> ArrayOfOrbs;
	int32 AmountOfOrbsLeft;
	
	TArray<FString> ArrayOrbsNames;
	

	
	void AddScore(int32 InAmount);
	void DamgePlayer(float InAmount);
	void LoseLife();
	void HealPlayer(float InAmount);
	void UpdatePlayerSpeed();
	
	
	
	void CheckGameState();
	
	void PrintDebugValues();
	
	
	
	//Input Function
	void InputHeal();
	void InputHealMax();
	void InputDamge();
	void InputAddScore();
	
	void MovePlayer(const FInputActionValue& Value);
	void InputStartSprint();
	void InputStopSprint();
	
	void UpdateOrb(AOrbAreanEnergyOrb* Orb);
	
	//void PlayerControlss();
	//void MovePlayerUnreal();
	//void MoveCharecter(FVector MoveDiraction, float DeltaTime);
};
