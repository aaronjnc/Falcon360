// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "FlightPoint.h"
#include "EnemyShip.h"
#include "LeadShip.h"
#include "Kismet/GameplayStatics.h"

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
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlightPoint::StaticClass(), FoundActors);
	PlayerCharacter = Cast<AVizParentPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	for (AActor* Actor : FoundActors)
	{
		AvailableFlightPoints.Add(Cast<AFlightPoint>(Actor));
	}
	for (int i = 0; i < LeadShipCount; i++)
	{
		AFlightPoint* Point = AvailableFlightPoints[FMath::RandRange(0, AvailableFlightPoints.Num()-1)];
		int RandomShip = FMath::RandRange(0, ShipTypes.Num()-1);
		FDataTableRowHandle ShipRow = ShipTypes[RandomShip];
		FActorSpawnParameters Params;
		AEnemyShip* EnemyShip = GetWorld()->SpawnActor<AEnemyShip>(EnemyShipSpawn, Point->GetActorLocation(), Point->GetActorRotation(), Params);
		ULeadShip* LeadShip = Cast<ULeadShip>(EnemyShip->AddComponentByClass(ULeadShip::StaticClass(), false, EnemyShip->GetActorTransform(), false));
		LeadShips.Add(LeadShip);
		LeadShip->SetStartingPoint(Point);
		EnemyShip->SetShipType(true, *ShipRow.DataTable->FindRow<FEnemyShips>(ShipRow.RowName, ""), LeadShip);
	}
	float RandWaitTime = FMath::RandRange(1.f, 5.f);
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyManager::ShipAttack, RandWaitTime, false);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemyManager::GetFlyUnderDistance()
{
	return FlyUnderDistance;
}

void AEnemyManager::ShipAttack()
{
	LeadShips[0]->BeginAttackRun();
}

void AEnemyManager::StopAttack(ULeadShip* StopAttacking)
{
	AttackingShips.Remove(StopAttacking);
	LeadShips.Add(StopAttacking);
}

bool AEnemyManager::ShouldAttack(ULeadShip* AttackShip)
{
	FVector NewShipLoc = AttackShip->GetOwner()->GetActorLocation();
	FRotator AttackShipRot = (NewShipLoc- PlayerCharacter->GetActorLocation()).Rotation();
	bool CanAttack = true;
	for (ULeadShip* AttackingShip : AttackingShips)
	{
		FVector AttackShipLoc = AttackingShip->GetOwner()->GetActorLocation();
		FRotator AttackerRot = (AttackShipLoc - PlayerCharacter->GetActorLocation()).Rotation();
		float AngleDiff = FMath::Abs(AttackShipRot.Yaw - AttackerRot.Yaw);
		float Distance = FMath::Abs((AttackShipLoc - NewShipLoc).Length());
		if (Distance / AngleDiff < AngleDistanceMultiplier)
		{
			return true;
		}
	}
	return CanAttack;
}

