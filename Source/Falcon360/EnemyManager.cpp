// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "FlightPoint.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < LeadShipCount; i++)
	{
		AFlightPoint* Point = AvailableFlightPoints[FMath::RandRange(0, AvailableFlightPoints.Num())];
		FActorSpawnParameters Params;
		LeadShips.Add(GetWorld()->SpawnActor<AEnemyShip>(AEnemyShip::StaticClass(), Point->GetActorLocation(), Point->GetActorRotation(), Params));
		//LeadShips[i]->SetShipType(true, )
		
	}
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

