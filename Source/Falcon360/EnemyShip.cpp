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
	if ((NextPointPosition - GetActorLocation()).Size() < 100)
	{
		GetNextPoint();
	}
	if (bAttacking)
	{
		TurretComponent->Shoot(false);
		TurretComponent->Shoot(true);
	} 
	if (bAttacking && (NextPointPosition - GetActorLocation()).Size() < DivertAttack)
	{
		bAttacking = false;
		GetNextPoint();
	}

}

void AEnemyShip::SetShipType(bool IsLeadShip, FEnemyShips ShipInfo, ULeadShip* NewLeadShip)
{
	LeadShip = NewLeadShip;
	StaticMeshComponent->SetStaticMesh(ShipInfo.StaticMesh);
	Health = ShipInfo.Health;
	Shield = ShipInfo.Shield;
	bLeadShip = IsLeadShip;
	TurretComponent->SetTurretInfo(ShipInfo.BlasterType, LeftBlaster, RightBlaster);
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
