// Fill out your copyright notice in the Description page of Project Settings.

#include "OrbAreanaEnemy.h"
#include "AOAPlayerCharecter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AOrbAreanaEnemy::AOrbAreanaEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// if (RootComponent == nullptr)
	// {
	// 	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	// }
	

	//HealWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	
	// Help By Unreals Ai Assistance To Set up The widge
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidgetComp->SetupAttachment(RootComponent);
	
	HealthWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
    
	// Space: Screen makes it always face the camera; Space: World keeps it in 3D
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComp->SetDrawAtDesiredSize(true);

}

// Called when the game starts or when spawned
void AOrbAreanaEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement() ->MaxWalkSpeed = EnemyAttribut.BaseSpeed;
	SetActorLabel( EnemyName );
	
	//PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	PlayerCharacter = Cast<AOAPlayerCharecter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	
	if (HealthWidgetComp)
	{
		HealthBarInstance = Cast<UHealthBar>(HealthWidgetComp->GetUserWidgetObject());
	}
}


// Called every frame
void AOrbAreanaEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer +=DeltaTime;
	EnemyPos = GetActorLocation();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	
	UpdateAI(DeltaTime,PlayerLocation);
	if (HealthBarInstance)
	{
		HealthBarInstance->Update(EnemyAttribut.Health, EnemyAttribut.MaxHealth);
	}

	if (Timer > EnemyAttribut.AtackkColdown)
	{
		if (DealDamgeToPlayer(EnemyAttribut.Damage, PlayerLocation))
		{
			Heal(EnemyAttribut.Damage);
			Timer = 0;
		}
	}
	if (bSeePlayer)
	{
		Move(PlayerLocation);
		
	}
	
	if (bDrawDebug)
	{
		DrawDebug();
		PrintDebugValues();
	}
	

}

// Called to bind functionality to input
void AOrbAreanaEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}

// Ai Behiver
bool AOrbAreanaEnemy::DealDamgeToPlayer(float DamgeAmount,FVector PlayerPos)
{
	if (not bSeePlayer)
	{
		return false;
	}
	if (IsValid(PlayerCharacter))
	{
		//FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float PlayerSize = PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
		float EnemySize = GetCapsuleComponent()->GetScaledCapsuleRadius();
		//FVector EnemyLoction = GetActorLocation();
		if(FVector::DistXY(EnemyPos, PlayerPos) <= EnemyAttribut.Range+EnemySize+PlayerSize-5) //
		{
			//Cast<AOAPlayerCharecter>(PlayerCharacter)->DamgePlayer(DamgeAmount);
			PlayerCharacter->DamgePlayer(DamgeAmount);
			return true;
		}
	}
	return false;
}

void AOrbAreanaEnemy::Heal(float HealAmount)
{
	EnemyAttribut.Health += HealAmount;
	//Health = FMath::Min(Health,MaxHealth);
	EnemyAttribut.Health = FMath::Clamp(EnemyAttribut.Health, 0.0f, EnemyAttribut.MaxHealth);
}

void AOrbAreanaEnemy::Move(FVector PlayerPos)
{
	// float X = PlayerPos.X - EnemyPos.X;
	// float Y = PlayerPos.Y- EnemyPos.Y;
	//
	// FVector2D Movment = {X,Y};
	// Movment.Normalize();
	//
	// AddMovementInput(GetActorForwardVector(), Movment.X);
	// AddMovementInput(GetActorRightVector(), Movment.Y);
	
	float EnemySize = GetCapsuleComponent()->GetScaledCapsuleRadius();

	if(FVector::DistXY(EnemyPos, PlayerPos) <= EnemyAttribut.Range+EnemySize)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(),EnemyAttribut.BaseSpeed);
}

void AOrbAreanaEnemy::UpdateAI(float DeltaTime, FVector PlayerPos)
{
	FVector VectorToPlayer = PlayerPos - EnemyPos;
	VectorToPlayer.Z = 0.f;
	FVector ToPlayerDiraction = VectorToPlayer.GetSafeNormal();
	
	FVector EnemyForwardVector = GetActorForwardVector();
	EnemyForwardVector.Z = 0.f;
	EnemyForwardVector = EnemyForwardVector.GetSafeNormal();
	
	// Dot prudukt
	DotPrukuktValue = FVector::DotProduct(EnemyForwardVector,ToPlayerDiraction);
	bSeePlayer = DotPrukuktValue > DotProduktSeePlayer;
	
	float EnemySize = GetCapsuleComponent()->GetScaledCapsuleRadius();
	if (not bSeePlayer or FVector::Dist2D(PlayerPos,EnemyPos) > MaxVeiwingRange+EnemySize)
	{
		bSeePlayer = false;
		DebugColor = {255,0,0};
		return;
	}
	// Cross
	CrossPrudoktValue = FVector::CrossProduct(EnemyForwardVector,ToPlayerDiraction);


	if (DotPrukuktValue > TresholdDotPrudukt )
	{
		return;
	}
	DebugColor = {0,255,0};
	float TurnDiraction = 1.f;
	
	if (CrossPrudoktValue.Z < 0)
	{
		TurnDiraction = -1.f;
	}
	if (CrossPrudoktValue.Z > 0)
	{
		TurnDiraction = 1.f;
	}
	
	float TurnAmunt = TurnDiraction*TurnSpeed*DeltaTime;
	
	AddActorLocalRotation(FRotator(0,TurnAmunt,0));
	
}

// Funksjns 
void AOrbAreanaEnemy::DamgeRecive(float DamgeAmount)
{
	EnemyAttribut.Health -=DamgeAmount;
}

// Debug
void AOrbAreanaEnemy::PrintDebugValues()
{
	GEngine->AddOnScreenDebugMessage(14,0.11f,FColor::Emerald,FString::Printf(TEXT("------------------------Enemy State---------------------")));
	GEngine->AddOnScreenDebugMessage(15,0.11f,FColor::Emerald,FString::Printf(TEXT("Heath: %f"),EnemyAttribut.Health));
	GEngine->AddOnScreenDebugMessage(16,0.11f,FColor::Emerald,FString::Printf(TEXT("Heath max Heath: %f"),EnemyAttribut.MaxHealth));
	
	GEngine->AddOnScreenDebugMessage(17,0.11f,FColor::Emerald,FString::Printf(TEXT("Damge: %f"),EnemyAttribut.Damage));
	GEngine->AddOnScreenDebugMessage(18,0.11f,FColor::Emerald,FString::Printf(TEXT("speed: %f"),EnemyAttribut.BaseSpeed));
}

void AOrbAreanaEnemy::DrawDebug()
{
	float EnemySize = GetCapsuleComponent()->GetScaledCapsuleRadius();
	DrawDebugSphere(GetWorld(),EnemyPos,EnemyAttribut.Range+EnemySize,10,DebugColor);
	DrawDebugDirectionalArrow(GetWorld(), EnemyPos, EnemyPos + GetActorForwardVector() * 150.f, 30.f, DebugColor, false, 0.f, 0, 3.f);
}
