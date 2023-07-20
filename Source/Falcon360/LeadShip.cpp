// Fill out your copyright notice in the Description page of Project Settings.


#include "LeadShip.h"

#include "EnemyManager.h"
#include "FlightPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULeadShip::ULeadShip()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULeadShip::BeginPlay()
{
	Super::BeginPlay();

	EnemyManager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyManager::StaticClass()));
	OwningShip = Cast<AEnemyShip>(GetOwner());
	FlyUnderLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(0, 0, EnemyManager->GetFlyUnderDistance());
}


// Called every frame
void ULeadShip::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULeadShip::BeginAttackRun()
{
	bAttacking = true;
	OwningShip->BeginAttack();
}

FVector ULeadShip::GetNextPoint()
{
	if (NextPosition == FlyUnderLocation)
	{
		bAttacking = false;
	}
	if (bAttacking)
	{
		EnemyManager->StopAttack(this);
		NextPosition = FlyUnderLocation;
		return FlyUnderLocation;
	}
	NextPoint = NextPoint->GetNextPoint();
	NextPosition = NextPoint->GetActorLocation();
	return NextPoint->GetActorLocation();
}

void ULeadShip::SetStartingPoint(AFlightPoint* FirstPoint)
{
	NextPoint = FirstPoint;
}

void ULeadShip::DestroyShip()
{
	EnemyManager->DestroyLeadShip(this);
}

APawn* ULeadShip::GetPlayer()
{
	return EnemyManager->GetPlayer();
}

