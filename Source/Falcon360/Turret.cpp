// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Laser.h"
#include "StructClass.h"
#include "GameFramework/FloatingPawnMovement.h"

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

	TurretInfos.Add(FTurretInfo());
	TurretInfos.Add(FTurretInfo());
}

void UTurret::SetTurretInfo(FDataTableRowHandle RowHandle, USceneComponent* LeftTurret, USceneComponent* RightTurret)
{
	TableRow = RowHandle;
	DelayTime = TableRow.DataTable->FindRow<FBlasters>(TableRow.RowName, "")->FireRate;
	TurretInfos[0].SceneComponent = LeftTurret;
	TurretInfos[1].SceneComponent = RightTurret;
}

void UTurret::Shoot(bool bLeft)
{
	int index = 0;
	if (!bLeft)
	{
		index = 1;
	}
	Fire(index);
}

void UTurret::Fire(int index)
{
	FActorSpawnParameters Params;
	ALaser* Laser = GetWorld()->SpawnActor<ALaser>(LaserSubclass, TurretInfos[index].SceneComponent->GetComponentLocation(), TurretInfos[index].SceneComponent->GetComponentRotation(), Params);
	UFloatingPawnMovement* MovementComponent = Cast<UFloatingPawnMovement>(GetOwner()->GetComponentByClass(UFloatingPawnMovement::StaticClass()));
	if (MovementComponent)
	{
		Laser->SetLaserType(TableRow.RowName, MovementComponent->Velocity);
	}
	else
	{
		Laser->SetLaserType(TableRow.RowName);
	}
}
