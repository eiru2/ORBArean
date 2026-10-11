// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanEnergyOrb.h"
#include "ORBArean/Charecters/AOAPlayerCharecter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ORBArean/widge/HealthBar.h"


// Sets default values
AOrbAreanEnergyOrb::AOrbAreanEnergyOrb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOrbAreanEnergyOrb::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	TArray<AOrbAreanEnergyOrb> EnergyOrbs;
	
}

// Called every frame
void AOrbAreanEnergyOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector OrbLocation = GetActorLocation();
	DrawDebugSphere(GetWorld(),OrbLocation,Radius,10,Color);

	if (IsValid(PlayerCharacter))
	{

		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float PlayerSize = PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
		if(FVector::DistXY(OrbLocation, PlayerLocation) <= PickUpRadius+PlayerSize) // Take place in one plane and keep player Size in mined
		{
			OrbPickedUp(OrbPointValue);
		}
	}
	

}

void AOrbAreanEnergyOrb::OrbPickedUp(int32 InPointValue)
{

	if (IsValid(PlayerCharacter))
	{
		Cast<AOAPlayerCharecter>(PlayerCharacter)->AddScore(InPointValue);
		UE_LOG(LogTemp,Warning,TEXT("Picked Up!! Orb %s Baind %d points"), *OrbName , OrbPointValue);
		Destroy();
		Cast<AOAPlayerCharecter>(PlayerCharacter)->UpdateOrb(this);
	}
}

