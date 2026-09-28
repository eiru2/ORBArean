// Fill out your copyright notice in the Description page of Project Settings.


#include "AOAPlayerCharecter.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"


// Sets default values
AOAPlayerCharecter::AOAPlayerCharecter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOAPlayerCharecter::BeginPlay()
{
	Super::BeginPlay();
	SetActorLabel( FString("dumbAss") );
	UpdatePlayerSpeed();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
	TArray<AActor*> EnergyOrbs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AOrbAreanEnergyOrb::StaticClass(),EnergyOrbs);
	
	for (AActor* Orb : EnergyOrbs)
	{
		ArrayOfOrbs.Add(Cast<AOrbAreanEnergyOrb>(Orb));
	}
	AmountOfOrbsLeft = ArrayOfOrbs.Num();
	
// HomeWork week 39
	TArray<int32> ArrayOfNum = {3,6,32,8,3,23,5,2,5,55,32,6,8,2,5,8};
	int32 Biggest = 0;
	for (int i = 0; i<ArrayOfNum.Num(); i++)
	{
		if (Biggest < ArrayOfNum[i])
		{
			Biggest = ArrayOfNum[i];
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Biggest Number = %d"), Biggest)
}


// Called every frame
void AOAPlayerCharecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UpdateOrb(ArrayOfOrbs);
	PrintDebugValues();
	CheckGameState();
}
// Called to bind functionality to input
void AOAPlayerCharecter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::MovePlayer);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AOAPlayerCharecter::InputStartSprint);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AOAPlayerCharecter::InputStopSprint);

	EnhancedInputComponent->BindAction(DamageAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputDamge);

	EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputHeal);
	
	EnhancedInputComponent->BindAction(HealActionMax, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputHealMax);

	EnhancedInputComponent->BindAction(AddScoreAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputAddScore);


}

void AOAPlayerCharecter::DamgePlayer(float InAmount)
{
	Health -= InAmount;
	if (Health <=0)
	{
		LoseLife();
	}
	if (Health <= 0.25*MaxHealth)
	{
		GEngine->AddOnScreenDebugMessage(8,2.11f,FColor::Emerald,TEXT("LowHealth"));
	}
	//Health = FMath::Min(Health,MaxHealth);
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void AOAPlayerCharecter::LoseLife()
{
	Life -=1;
	Life = FMath::Clamp(Life, 0.0f, MaxLife);
	Health = MaxHealth;
	if (Life == 0)
	{
		GameState = EGameState::Lost;
	}
		
}

void AOAPlayerCharecter::AddScore(int32 InAmount)
{
	Score +=InAmount;
	if (Score >= 1000)
	{
		GameDifficulty = EGameDifficulty::Hard;
	}
	else if (Score > 500 and Score < 1000)
	{
		GameDifficulty = EGameDifficulty::Medium;
	}
	else if (Score <= 500)
	{
		GameDifficulty = EGameDifficulty::Easy;
	}
	UpdatePlayerSpeed();
}

void AOAPlayerCharecter::HealPlayer(float InAmount)
{
	Health += InAmount;
	//Health = FMath::Min(Health,MaxHealth);
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void AOAPlayerCharecter::UpdatePlayerSpeed()
{
	switch(GameDifficulty)
	{
		case EGameDifficulty::Easy:
			CurrentMovmentSpeed = EasyMovmentSpeed;
			break;
		case EGameDifficulty::Medium:
			CurrentMovmentSpeed = MediumMovmentSpeed;
			break;
		case EGameDifficulty::Hard:
			CurrentMovmentSpeed = HardMovmentSpeed;
			break;
	}
	float SpeedMultiplier = 1.f;
	if (Sprinting)
	{
		SpeedMultiplier += SprintMultiplier; 
	}
	
	GetCharacterMovement() ->MaxWalkSpeed = CurrentMovmentSpeed*SpeedMultiplier;
	Acceleration = CurrentMovmentSpeed*2;
	GetCharacterMovement() ->MaxAcceleration = Acceleration;	
}

void AOAPlayerCharecter::CheckGameState()
{
	if (Life <=0)
	{
		GameState =  EGameState::Lost;
		UE_LOG(LogTemp, Warning, TEXT("Game Lost"))
	}
	else if (Score >= ScoreWinCondition)
	{
		GameState =  EGameState::Won;
		UE_LOG(LogTemp, Warning, TEXT("Game Won"))
	}
	else if (AmountOfOrbsLeft <=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Orb Left"))
	}
	
}

void AOAPlayerCharecter::PrintDebugValues()
{
	GEngine->AddOnScreenDebugMessage(1,0.11f,FColor::Emerald,FString::Printf(TEXT("Score: %i"), Score));
	GEngine->AddOnScreenDebugMessage(2,0.11f,FColor::Emerald,FString::Printf(TEXT("Player Health: %.2f"), Health));
	GEngine->AddOnScreenDebugMessage(3,0.11f,FColor::Emerald,FString::Printf(TEXT("Player Life: %i"), Life));
	GEngine->AddOnScreenDebugMessage(8,0.11f,FColor::Emerald,FString::Printf(TEXT("Player pos: %s"), *GetActorLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(9,0.11f,FColor::Emerald,FString::Printf(TEXT("Player sprinting: %i"), Sprinting));
	GEngine->AddOnScreenDebugMessage(10,0.11f,FColor::Emerald,FString::Printf(TEXT("Orbs Left: %i"), AmountOfOrbsLeft));
	
	
	if (CurrentMovmentSpeed > 2000.0f)
	{
		
		GEngine->AddOnScreenDebugMessage(4,0.11f,FColor::Red,FString::Printf(TEXT("Player is Sonic!! Movement Speed: %.2f"), CurrentMovmentSpeed));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(4,0.11f,FColor::Red,FString::Printf(TEXT("Player Movement Speed: %.2f"), CurrentMovmentSpeed));
	}
	GEngine->AddOnScreenDebugMessage(5,0.11f,FColor::Red,FString::Printf(TEXT("Player Name: %s"), *Name));
	switch(GameState){
		case  EGameState::Playing:
			GEngine->AddOnScreenDebugMessage(6,0.11f,FColor::Red,FString::Printf(TEXT("Game Playing: %i"), GameState));
			break;
		case  EGameState::Won:
			GEngine->AddOnScreenDebugMessage(6,0.11f,FColor::Red,FString::Printf(TEXT("Game Won %i"), GameState));
			break;
		case  EGameState::Lost:
			GEngine->AddOnScreenDebugMessage(6,0.11f,FColor::Red,FString::Printf(TEXT("Game lost %i"), GameState));
			break;
	}
	switch(GameDifficulty){
		case EGameDifficulty::Easy:
			GEngine->AddOnScreenDebugMessage(7,0.11f,FColor::Red,FString::Printf(TEXT("Game Difficulty Esay: %i"), GameDifficulty));
			break;
		case EGameDifficulty::Medium:
			GEngine->AddOnScreenDebugMessage(7,0.11f,FColor::Red,FString::Printf(TEXT("Game Difficulty Medium: %i"), GameDifficulty));
			break;
		case EGameDifficulty::Hard:
			GEngine->AddOnScreenDebugMessage(7,0.11f,FColor::Red,FString::Printf(TEXT("Game Difficulty Hard: %i"), GameDifficulty));
			break;
	}

	PlayerPos = GetActorLocation().ToString();
	//GEngine->AddOnScreenDebugMessage(8,0.11f,FColor::Red,FString::Printf(TEXT("Player loction %s"), *PlayerPos));
}





void AOAPlayerCharecter::MovePlayer(const FInputActionValue& Value)
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	FVector2D MovementValue = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementValue.X);
	AddMovementInput(GetActorRightVector(), MovementValue.Y);
}


// Input Calls
void AOAPlayerCharecter::InputHeal()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	
	HealPlayer(TempHeal);
}

void AOAPlayerCharecter::InputHealMax()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	HealPlayer(MaxHealth);
}

void AOAPlayerCharecter::InputDamge()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	DamgePlayer(TempDamge);
}
void AOAPlayerCharecter::InputAddScore()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	AddScore(TempScore);
}

// void AOAPlayerCharecter::InputMove();
void AOAPlayerCharecter::InputStartSprint()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	Sprinting = TRUE;
	UpdatePlayerSpeed();
}
void AOAPlayerCharecter::InputStopSprint()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	Sprinting = FALSE;
	UpdatePlayerSpeed();
}

void AOAPlayerCharecter::UpdateOrb(TArray<AOrbAreanEnergyOrb*> ArrayOrbs)
{
	for (AOrbAreanEnergyOrb* Orb : ArrayOrbs)
	{
		if (not IsValid(Orb))
		{
			ArrayOfOrbs.Remove(Orb);
			AmountOfOrbsLeft--;
			UE_LOG(LogTemp, Warning, TEXT("Orb Aray Length %d pointers"),ArrayOfOrbs.Num())
		}
	}
}


// void AOAPlayerCharecter::MovePlayer(float DeltaTime)
// {
// 	FVector MoveDedication = FVector::ZeroVector;
// 	FVector CurrentPos = GetActorLocation();
// 	//if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
// 	if (APlayerController* PC = Cast<APlayerController>(GetController()))
// 	{
// 		if (GameState == Playing)
// 		{
// 			if(PC->IsInputKeyDown(EKeys::W))
// 			{
// 				MoveDedication.X += 1.f;
// 			}
// 			if(PC->IsInputKeyDown(EKeys::S))
// 			{
// 				MoveDedication.X -= 1.f;
// 			}
// 			if(PC->IsInputKeyDown(EKeys::D))
// 			{
// 				MoveDedication.Y += 1.f;
// 			}
// 			if(PC ->IsInputKeyDown(EKeys::A))
// 			{
// 				MoveDedication.Y -= 1.f;	
// 			}
// 			if (PC -> IsInputKeyDown(EKeys::LeftShift))
// 			{
// 				Sprinting = true;
// 			}
// 			else
// 			{
// 				Sprinting = false;
// 			}
// 			MoveCharecter(MoveDedication,DeltaTime);
// 		}
//
// 	}
// 	
// }

// void AOAPlayerCharecter::MovePlayerUnreal()
// {
// 	if (APlayerController* PC = Cast<APlayerController>(GetController()))
// 	{
// 		if (PC -> IsInputKeyDown(EKeys::LeftShift))
// 		{
// 			Sprinting = true;
// 		}
// 		else
// 		{
// 			Sprinting = false;
// 		}
// 		if (Sprinting)
// 		{
// 			GetCharacterMovement()->MaxWalkSpeed = CurrentMovmentSpeed*SprintMultiplier;
// 		}
// 		else
// 		{
// 			GetCharacterMovement()->MaxWalkSpeed = CurrentMovmentSpeed;
// 		}
// 		
// 		if(PC->IsInputKeyDown(EKeys::W))
// 		{
// 			AddMovementInput(GetActorForwardVector(), 1.f);
// 		}
// 		if(PC->IsInputKeyDown(EKeys::S))
// 		{
// 			AddMovementInput(GetActorForwardVector(), -1.f);
// 		}
// 		if(PC->IsInputKeyDown(EKeys::D))
// 		{
// 			AddMovementInput(GetActorRightVector(), 1.f);
// 		}
// 		if(PC ->IsInputKeyDown(EKeys::A))
// 		{
// 			AddMovementInput(GetActorRightVector(),- 1.f);	
// 		}
// 	}
// }

// void AOAPlayerCharecter::PlayerControlss()
// {
// 	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
// 	{
// 		if (GameState == EGameState::Playing)
// 		{
// 			if(PC->IsInputKeyDown(EKeys::One))
// 			{
// 				DamgePlayer(TempDamge);
// 			}
// 			if(PC->IsInputKeyDown(EKeys::Two))
// 			{
// 				HealPlayer(TempHeal);
// 			}
// 			if(PC->IsInputKeyDown(EKeys::Three))
// 			{
// 				AddScore( TempScore);
// 			}
// 			
// 		}
// 	} 
// }

// void AOAPlayerCharecter::MoveCharecter(FVector MoveDiraction, float DeltaTime)
// {
// 	if(Sprinting)
// 	{
// 		FVector CurrentPos = GetActorLocation();
// 		MoveDiraction = MoveDiraction.GetSafeNormal();
// 		const FVector MoveThisFrame = MoveDiraction* CurrentMovmentSpeed*SprintMultiplier*DeltaTime;
// 		const FVector NewLocation = CurrentPos +MoveThisFrame;
// 		SetActorLocation(NewLocation);
// 	}
// 	else
// 	{
// 		FVector CurrentPos = GetActorLocation();
// 		MoveDiraction = MoveDiraction.GetSafeNormal();
// 		const FVector MoveThisFrame = MoveDiraction* CurrentMovmentSpeed*DeltaTime;
// 		const FVector NewLocation = CurrentPos +MoveThisFrame;
// 		SetActorLocation(NewLocation);
// 	}
// }
