// Fill out your copyright notice in the Description page of Project Settings.


#include "AOAPlayerCharecter.h"
#include "OrbAreanaEnemy.h"

#include "EnhancedInputComponent.h"
#include "MeshPaintVisualize.h"
#include "Components/CapsuleComponent.h"
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

	
	// DifficultySpeedMultiplier.Add(EGameDifficulty::Easy, 1.0f);
	// DifficultySpeedMultiplier.Add(EGameDifficulty::Medium, 0.75f);
	// DifficultySpeedMultiplier.Add(EGameDifficulty::Hard, 0.5f);
	

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

	ArraOfEnemy = GetEnemCharecter();
	
	TArray<AActor*> EnergyOrbs;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AOrbAreanEnergyOrb::StaticClass(),EnergyOrbs);
	
	for (AActor* Orb : EnergyOrbs)
	{
		ArrayOfOrbs.Add(Cast<AOrbAreanEnergyOrb>(Orb));
		ArrayOrbsNames.Add(Cast<AOrbAreanEnergyOrb>(Orb)->OrbName);
	}
	AmountOfOrbsLeft = ArrayOfOrbs.Num();
	
	
	for (int i = 0; i < ArrayOrbsNames.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Orb name = %s"), *ArrayOrbsNames[i] );
	}
	
	for (FString Orb : ArrayOrbsNames)
	{
		if (Orb == "No.29")
		{
			UE_LOG(LogTemp, Warning, TEXT("Orb name %s exsiste"), *Orb );
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------") )
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
	
	
	// UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------") )
	// UE_LOG(LogTemp, Warning, TEXT("Enemy Health %f"), Enemy.Health )
	// UE_LOG(LogTemp, Warning, TEXT("Enemy Max Health %f"), Enemy.MaxHealth )
	// UE_LOG(LogTemp, Warning, TEXT("Enemy Base speed %f"), Enemy.BaseSpeed )
	// UE_LOG(LogTemp, Warning, TEXT("Enemy Damage %f"), Enemy.Damage )
	
	UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------") )
	for (FLootDrop LootDrop : ArrayLootDrop)
	{
		UE_LOG(LogTemp, Warning, TEXT("--------------New Loot--------------") )
		UE_LOG(LogTemp, Warning, TEXT("LootName %s"), *LootDrop.Name )
		UE_LOG(LogTemp, Warning, TEXT("Value %f"), LootDrop.Value )
		// int32 temp = LootDrop.Rarity;
		// FText Rarty;
		// UEnum::GetDisplayValueAsText(LootDrop.Rarity, Rarty);
		// UE_LOG(LogTemp, Warning, TEXT("Rarty %s"), *Rarty.ToString())
		UE_LOG(LogTemp, Warning, TEXT("Rarty %s"),*LootDrop.RartyLabel[LootDrop.Rarity])
	}
	
	UE_LOG(LogTemp, Warning, TEXT("---------------------------------------------") )
	Biggest = 0;
	for (int i = 0; i<ArrayLootDrop.Num(); i++)
	{
		if (ArrayLootDrop[Biggest].Value < ArrayLootDrop[i].Value)
		{
			Biggest = i;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Biggest Loot Value = %s"), *ArrayLootDrop[Biggest].Name)
	
}


// Called every frame
void AOAPlayerCharecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UpdateOrb(ArrayOfOrbs);
	PrintDebugValues();
	CheckGameState();
	int32 i = 0;

	
	
}
// Called to bind functionality to input
void AOAPlayerCharecter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::MovePlayer);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AOAPlayerCharecter::InputStartSprint);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AOAPlayerCharecter::InputStopSprint);

	EnhancedInputComponent->BindAction(DamageActionTesst, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputReciveDamge);
	
	EnhancedInputComponent->BindAction(DealDamageAction,ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputDealDamge);

	EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputHeal);
	
	EnhancedInputComponent->BindAction(HealActionMax, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputHealMax);

	EnhancedInputComponent->BindAction(AddScoreAction, ETriggerEvent::Triggered, this, &AOAPlayerCharecter::InputAddScore);


}

// Damge
void AOAPlayerCharecter::DamgePlayer(float InAmount)
{
	
	PlayerAttribute.Health -= InAmount;
	if (PlayerAttribute.Health <=0)
	{
		LoseLife();
	}
	if (PlayerAttribute.Health <= 0.25*PlayerAttribute.MaxHealth)
	{
		GEngine->AddOnScreenDebugMessage(8,2.11f,FColor::Emerald,TEXT("LowHealth"));
	}
	//Health = FMath::Min(Health,MaxHealth);
	PlayerAttribute.Health = FMath::Clamp(PlayerAttribute.Health, 0.0f, PlayerAttribute.MaxHealth);
}

void AOAPlayerCharecter::DealDamge(AOrbAreanaEnemy*)
{
	
}

// Player Movment
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

void AOAPlayerCharecter::UpdatePlayerSpeed()
{
	// switch(GameDifficulty)
	// {
	// 	case EGameDifficulty::Easy:
	// 		CurrentMovmentSpeed = EasyMovmentSpeed;
	// 		break;
	// 	case EGameDifficulty::Medium:
	// 		CurrentMovmentSpeed = MediumMovmentSpeed;
	// 		break;
	// 	case EGameDifficulty::Hard:
	// 		CurrentMovmentSpeed = HardMovmentSpeed;
	// 		break;
	// }
	float SpeedMultiplier = 1.f;
	if (Sprinting)
	{
		SpeedMultiplier += SprintMultiplier; 
	}
	
	//CurrentMovmentSpeed = PlayerAttribute.BaseSpeed*DifficultySpeedMultiplier.FindRef(GameDifficulty)*SpeedMultiplier;
	CurrentMovmentSpeed = PlayerAttribute.BaseSpeed*DifficultySpeedMultiplier[static_cast<int>(GameDifficulty)]*SpeedMultiplier;
	GetCharacterMovement() ->MaxWalkSpeed = CurrentMovmentSpeed;
	Acceleration = CurrentMovmentSpeed*2;
	GetCharacterMovement() ->MaxAcceleration = Acceleration;	
}

// Health System
void AOAPlayerCharecter::HealPlayer(float InAmount)
{
	PlayerAttribute.Health += InAmount;
	//Health = FMath::Min(Health,MaxHealth);
	PlayerAttribute.Health = FMath::Clamp(PlayerAttribute.Health, 0.0f, PlayerAttribute.MaxHealth);
}

void AOAPlayerCharecter::LoseLife()
{
	PlayerAttribute.Life -=1;
	PlayerAttribute.Life = FMath::Clamp(PlayerAttribute.Life, 0.0f, PlayerAttribute.MaxLife);
	PlayerAttribute.Health = PlayerAttribute.MaxHealth;
	if (PlayerAttribute.Life == 0)
	{
		GameState = EGameState::Lost;
	}
		
}


// System
void AOAPlayerCharecter::CheckGameState()
{
	if (PlayerAttribute.Life <=0)
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
	HealPlayer(PlayerAttribute.MaxHealth);
}

void AOAPlayerCharecter::InputReciveDamge()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	DamgePlayer(TempDamge);
}

void AOAPlayerCharecter::InputDealDamge()
{
	if (GameState != EGameState::Playing)
	{
		return;
	}
	
	TArray<AOrbAreanaEnemy*> ToRemoveList;
	
	FVector PlayerLoctionVector = GetActorLocation();
	float PlayerRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	DrawDebugSphere(GetWorld(),PlayerLoctionVector,PlayerRadius+PlayerAttribute.Range,10,FColor(255,0,0),false, 1);
	for (AOrbAreanaEnemy* Enemy : ArraOfEnemy)
	{
		FVector EnemyPos = Enemy->GetActorLocation();
		float EnemySize = Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius();
		if (FVector::Dist2D(PlayerLoctionVector,EnemyPos) < PlayerAttribute.Range+PlayerRadius+ EnemySize)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enem,y Health before %f"), Enemy->EnemyAttribut.Health)
			Enemy->DamgeRecive(PlayerAttribute.Damage);
			UE_LOG(LogTemp, Warning, TEXT("Enem,y Health After %f"), Enemy->EnemyAttribut.Health)
			if (Enemy->EnemyAttribut.Health <= 0)
			{
				ToRemoveList.Add(Enemy);
			}
		}
	}
	
	for (AOrbAreanaEnemy* Enemy : ToRemoveList)
	{
		ArraOfEnemy.Remove(Enemy);
		Enemy->Destroy();
	}
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

void AOAPlayerCharecter::UpdateOrb(AOrbAreanEnergyOrb* Orb)
{
	if (Orb)
	{
		ArrayOfOrbs.Remove(Orb);
		AmountOfOrbsLeft--;
		UE_LOG(LogTemp, Warning, TEXT("Orb Aray Length %d pointers"),ArrayOfOrbs.Num())
		
	}
}

// Setupp
TArray<AOrbAreanaEnemy*> AOAPlayerCharecter::GetEnemCharecter()
{
	TArray<AActor*> EnemyCharecter;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AOrbAreanaEnemy::StaticClass(),EnemyCharecter);
	
	TArray<AOrbAreanaEnemy*> RerunList;
	for (AActor* Enemy : EnemyCharecter)
	{
		RerunList.Add(Cast<AOrbAreanaEnemy>(Enemy));
		UE_LOG(LogTemp, Warning, TEXT("Enemy %.f"),Cast<AOrbAreanaEnemy>(Enemy)->EnemyAttribut.Health)

	}

	return RerunList;
}

// Debug
void AOAPlayerCharecter::PrintDebugValues()
{
	GEngine->AddOnScreenDebugMessage(1,0.11f,FColor::Emerald,FString::Printf(TEXT("------------------------Player State---------------------")));
	GEngine->AddOnScreenDebugMessage(2,0.11f,FColor::Emerald,FString::Printf(TEXT("Player Health: %.2f"), PlayerAttribute.Health));
	GEngine->AddOnScreenDebugMessage(3,0.11f,FColor::Emerald,FString::Printf(TEXT("Player Life: %i"), PlayerAttribute.Life));
	
	GEngine->AddOnScreenDebugMessage(4,0.11f,FColor::Red,FString::Printf(TEXT("------------------------Player Speed---------------------")));
	GEngine->AddOnScreenDebugMessage(5,0.11f,FColor::Red,FString::Printf(TEXT("Player pos: %s"), *GetActorLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(6,0.11f,FColor::Red,FString::Printf(TEXT("Player sprinting: %i"), Sprinting));
	if (CurrentMovmentSpeed > 2000.0f)
	{
		
		GEngine->AddOnScreenDebugMessage(7,0.11f,FColor::Red,FString::Printf(TEXT("Player is Sonic!! Movement Speed: %.2f"), CurrentMovmentSpeed));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(7,0.11f,FColor::Red,FString::Printf(TEXT("Player Movement Speed: %.2f"), CurrentMovmentSpeed));
	}
	
	GEngine->AddOnScreenDebugMessage(8,0.11f,FColor::Yellow,FString::Printf(TEXT("------------------------Game Info---------------------")));
	GEngine->AddOnScreenDebugMessage(9,0.11f,FColor::Yellow,FString::Printf(TEXT("Score: %i"), Score));
	GEngine->AddOnScreenDebugMessage(10,0.11f,FColor::Yellow,FString::Printf(TEXT("Orbs Left: %i"), AmountOfOrbsLeft));
	switch(GameState){
		case  EGameState::Playing:
			GEngine->AddOnScreenDebugMessage(11,0.11f,FColor::Yellow,FString::Printf(TEXT("Game Playing: %i"), GameState));
			break;
		case  EGameState::Won:
			GEngine->AddOnScreenDebugMessage(11,0.11f,FColor::Yellow,FString::Printf(TEXT("Game Won %i"), GameState));
			break;
		case  EGameState::Lost:
			GEngine->AddOnScreenDebugMessage(11,0.11f,FColor::Yellow,FString::Printf(TEXT("Game lost %i"), GameState));
			break;
	}
	switch(GameDifficulty){
		case EGameDifficulty::Easy:
			GEngine->AddOnScreenDebugMessage(12,0.11f,FColor::Yellow,FString::Printf(TEXT("Game Difficulty Esay: %i"), GameDifficulty));
			break;
		case EGameDifficulty::Medium:
			GEngine->AddOnScreenDebugMessage(12,0.11f,FColor::Yellow,FString::Printf(TEXT("Game Difficulty Medium: %i"), GameDifficulty));
			break;
		case EGameDifficulty::Hard:
			GEngine->AddOnScreenDebugMessage(12,0.11f,FColor::Yellow,FString::Printf(TEXT("Game Difficulty Hard: %i"), GameDifficulty));
			break;
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
