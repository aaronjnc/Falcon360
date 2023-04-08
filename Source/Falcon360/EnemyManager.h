// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyShip.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class FALCON360_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Spawn Info")
	int LeadShipCount;

	UPROPERTY(EditAnywhere, Category = "Spawn Info")
	TArray<FDataTableRowHandle> ShipTypes;

	UPROPERTY()
	TArray<AEnemyShip*> LeadShips;

	UPROPERTY()
	TArray<AFlightPoint*> AvailableFlightPoints;

	UPROPERTY()
	TArray<AFlightPoint*> TakenFlightPoints;

};
