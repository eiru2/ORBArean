// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbAreanProjectile.h"

#include "SNegativeActionButton.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ORBArean/Charecters/OrbAreanaEnemy.h"


// Sets default values
AOrbAreanProjectile::AOrbAreanProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent->SetupAttachment(RootComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovment");
	
}

void AOrbAreanProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	
	OnActorBeginOverlap.AddDynamic(this, &AOrbAreanProjectile::DamageEnemy);
}

void AOrbAreanProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrbAreanProjectile::DamageEnemy(AActor* ThisAcoter, AActor* OtherActor)
{
	AOrbAreanaEnemy* Enemy = Cast<AOrbAreanaEnemy>(OtherActor);
	
	if (IsValid(Enemy))
	{
		Enemy->DamgeRecive(DamageValue);
		UE_LOG(LogTemp, Warning, TEXT("Enemy %.s"), *Enemy->EnemyName)
		this->Destroy();
	}
	
}


