// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Laser.h"

struct FBlasters;
// Sets default values for this component's properties
UTurret::UTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTurret::Shoot(FVector Location, FRotator Direction)
{
	FActorSpawnParameters Params;
	ALaser* Laser = GetWorld()->SpawnActor<ALaser>(LaserSubclass, Location, Direction, Params);
	Laser->SetLaserType(TableRow.RowName);
}

