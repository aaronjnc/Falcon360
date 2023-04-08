// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"

#include "EnemyManager.h"
#include "FlightPoint.h"
#include "StructClass.h"
#include "Turret.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AEnemyShip::AEnemyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

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
	FRotator NewRotation = FMath::FInterpConstantTo(GetActorRotation(), GoalRotation, DeltaTime, RotateSpeed);
	SetActorRotation(NewRotation);
	MovementComponent->Velocity = GetActorForwardVector() * Speed;
	if ((NextPointPosition - GetActorLocation()).Size() < 100)
	{
		SetNextPoint(NextPoint->GetNextPoint());
	}
}

void AEnemyShip::SetShipType(bool IsLeadShip, FEnemyShips ShipInfo)
{
	StaticMeshComponent->SetStaticMesh(ShipInfo.StaticMesh);
	Health = ShipInfo.Health;
	Shield = ShipInfo.Shield;
	bLeadShip = IsLeadShip;
}

void AEnemyShip::SetNextPoint(AFlightPoint* NextFlightPoint)
{
	NextPoint = NextFlightPoint;
	NextPointPosition = NextPoint->GetActorLocation();
}

