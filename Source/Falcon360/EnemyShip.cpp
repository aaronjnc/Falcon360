// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"

#include "EnemyManager.h"
#include "FlightPoint.h"
#include "LeadShip.h"
#include "StructClass.h"
#include "Turret.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AEnemyShip::AEnemyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	TurretComponent = CreateDefaultSubobject<UTurret>(TEXT("Turret Component"));

	LeftBlaster = CreateDefaultSubobject<USceneComponent>(TEXT("Left Blaster"));
	LeftBlaster->SetupAttachment(StaticMeshComponent);
	
	RightBlaster = CreateDefaultSubobject<USceneComponent>(TEXT("Right Blaster"));
	RightBlaster->SetupAttachment(StaticMeshComponent);

}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator GoalRotation = (NextPointPosition - GetActorLocation()).Rotation();
	FRotator NewRotation =FMath::RInterpConstantTo(GetActorRotation(), GoalRotation, DeltaTime, RotateSpeed);
	SetActorRotation(NewRotation);
	MovementComponent->Velocity = GetActorForwardVector() * Speed;
	if (bAttacking)
	{
		AngleDiff = FMath::Clamp(FVector::DotProduct(GoalRotation.Euler(), NewRotation.Euler()),0, 360);
	}
	if (bAttacking && (AngleDiff < 3 || AngleDiff > 357))
	{
		const FRotator LeftRotation = (NextPointPosition - LeftBlaster->GetComponentLocation()).Rotation();
		LeftBlaster->SetWorldRotation(LeftRotation);
		const FRotator RightRotation = (NextPointPosition - RightBlaster->GetComponentLocation()).Rotation();
		RightBlaster->SetWorldRotation(RightRotation);
		if (!bShooting)
		{
			bShooting = true;
			TurretComponent->Shoot(false);
			TurretComponent->Shoot(true);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, FireRate, false);
		}
	}
	else if (bShooting)
	{
		bShooting = false;
	}
	if ((NextPointPosition - GetActorLocation()).Size() < 100)
	{
		GetNextPoint();
	}
	if (bAttacking && (NextPointPosition - GetActorLocation()).Size() < DivertAttack)
	{
		bShooting = false;
		GetNextPoint();
	}

}

void AEnemyShip::SetShipType(bool IsLeadShip, FEnemyShips ShipInfo, ULeadShip* NewLeadShip)
{
	LeadShip = NewLeadShip;
	StaticMeshComponent->SetStaticMesh(ShipInfo.StaticMesh);
	MaxHealth = ShipInfo.Health;
	Health = MaxHealth;
	MaxShield = ShipInfo.Shield;
	Shield = MaxShield;
	bLeadShip = IsLeadShip;
	FireRate = ShipInfo.BlasterType.DataTable->FindRow<FBlasters>(ShipInfo.BlasterType.RowName, "")->FireRate;
	TurretComponent->SetTurretInfo(ShipInfo.BlasterType, LeftBlaster, RightBlaster);
	TimerDelegate.BindUFunction(this, "ContinueShooting");
	SetActorScale3D(FVector(ShipInfo.Scale, ShipInfo.Scale, ShipInfo.Scale));
	GetNextPoint();
}

void AEnemyShip::SetDestination(FVector Destination)
{
	NextPointPosition = Destination;
}

void AEnemyShip::GetNextPoint()
{
	if (bLeadShip)
	{
		SetDestination(LeadShip->GetNextPoint());
	}
}

void AEnemyShip::BeginAttack()
{
	bAttacking = true;
	SetDestination(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}

float AEnemyShip::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Remaining = FMath::Clamp(DamageAmount - Shield, 0, DamageAmount);
	Shield = FMath::Clamp(Shield - DamageAmount, 0, MaxShield);
	float FinalRemaining = FMath::Clamp(Remaining - Health, 0, Remaining);
	Health = FMath::Clamp(Health - Remaining, 0, MaxHealth);
	if (Health <= 0)
	{
		Destroy();
	}
	return Health;
}

void AEnemyShip::ContinueShooting()
{
	if (bShooting)
	{
		TurretComponent->Shoot(true);
		TurretComponent->Shoot(false);
	}
}
