// Fill out your copyright notice in the Description page of Project Settings.

#include "ORBArean/Charecters/AOAPlayerCharecter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OrbAreanaEnemy.h"

// Sets default values
AOrbAreanaEnemy::AOrbAreanaEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrbAreanaEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement() ->MaxWalkSpeed = EnemyAttribut.BaseSpeed;
	
	//PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	PlayerCharacter = Cast<AOAPlayerCharecter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
}

// Called every frame
void AOrbAreanaEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector EnemyLoction = GetActorLocation();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	
	DealDamgeToPlayer(EnemyAttribut.Damage, EnemyLoction, PlayerLocation);
	Move(EnemyLoction,PlayerLocation);
	Heal(1);
	PrintDebugValues();
	

}

// Called to bind functionality to input
void AOrbAreanaEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}


void AOrbAreanaEnemy::DealDamgeToPlayer(float DamgeAmount, FVector EnemyPos,FVector PlayerPos)
{
	if (IsValid(PlayerCharacter))
	{
		//FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float PlayerSize = PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
		float EnemySize = GetCapsuleComponent()->GetScaledCapsuleRadius();
		//FVector EnemyLoction = GetActorLocation();
		if(FVector::DistXY(EnemyPos, PlayerPos) <= EnemyAttribut.Range+PlayerSize+EnemySize) //
		{
			//Cast<AOAPlayerCharecter>(PlayerCharacter)->DamgePlayer(DamgeAmount);
			PlayerCharacter->DamgePlayer(DamgeAmount);
		}
	}
}

void AOrbAreanaEnemy::Heal(float HealAmount)
{
	EnemyAttribut.Health += HealAmount;
	//Health = FMath::Min(Health,MaxHealth);
	EnemyAttribut.Health = FMath::Clamp(EnemyAttribut.Health, 0.0f, EnemyAttribut.MaxHealth);
}

void AOrbAreanaEnemy::PrintDebugValues()
{
	GEngine->AddOnScreenDebugMessage(14,0.11f,FColor::Emerald,FString::Printf(TEXT("------------------------Enemy State---------------------")));
	GEngine->AddOnScreenDebugMessage(15,0.11f,FColor::Emerald,FString::Printf(TEXT("Heath: %f"),EnemyAttribut.Health));
	GEngine->AddOnScreenDebugMessage(16,0.11f,FColor::Emerald,FString::Printf(TEXT("Heath max Heath: %f"),EnemyAttribut.MaxHealth));
	
	GEngine->AddOnScreenDebugMessage(17,0.11f,FColor::Emerald,FString::Printf(TEXT("Damge: %f"),EnemyAttribut.Damage));
	GEngine->AddOnScreenDebugMessage(18,0.11f,FColor::Emerald,FString::Printf(TEXT("speed: %f"),EnemyAttribut.BaseSpeed));
}

void AOrbAreanaEnemy::Move(FVector EnemyPos,FVector PlayerPos)
{
	float X = PlayerPos.X - EnemyPos.X;
	float Y = PlayerPos.Y- EnemyPos.Y;
	
	FVector2D Movment = {X,Y};
	Movment.Normalize();
	
	AddMovementInput(GetActorForwardVector(), Movment.X);
	AddMovementInput(GetActorRightVector(), Movment.Y);
}

