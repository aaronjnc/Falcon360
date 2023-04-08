// Fill out your copyright notice in the Description page of Project Settings.


#include "FlightPoint.h"

// Sets default values
AFlightPoint::AFlightPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlightPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

EFlightPoints AFlightPoint::GetFlightPointType() const
{
	return PointType;
}

AFlightPoint* AFlightPoint::GetNextPoint() const
{
	return NextPoint;
}

AFlightPoint* AFlightPoint::GetPreviousPoint() const
{
	return PreviousPoint;
}

TArray<AFlightPoint*> AFlightPoint::GetAdjacentPoints() const
{
	return AdjacentPoints;
}


