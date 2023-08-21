// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VizParentPawn.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AFlightPoint;
class AEnemyShip;
struct FDataTableRowHandle;
class ULeadShip;

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

	void SpawnWave();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetFlyUnderDistance();

	UFUNCTION()
	void ShipAttack();

	UFUNCTION()
	void StopAttack(ULeadShip* StopAttacking);

	UFUNCTION()
	bool ShouldAttack(ULeadShip* AttackShip);

	UFUNCTION()
	void DestroyLeadShip(ULeadShip* Destroyed);

	UFUNCTION()
	APawn* GetPlayer();

private:

	UPROPERTY(EditAnywhere, Category = "Spawn Info")
	int LeadShipCount;

	UPROPERTY(EditAnywhere, Category = "Spawn Info")
	TArray<FDataTableRowHandle> ShipTypes;

	UPROPERTY()
	TArray<ULeadShip*> LeadShips;

	UPROPERTY()
	TArray<ULeadShip*> AttackingShips;

	UPROPERTY()
	TArray<AFlightPoint*> AvailableFlightPoints;

	UPROPERTY()
	TArray<AFlightPoint*> TakenFlightPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn info")
	TSubclassOf<AEnemyShip> EnemyShipSpawn;

	UPROPERTY()
	bool bAttackingShip;

	UPROPERTY(EditAnywhere, Category = "Attack Info")
	float FlyUnderDistance;

	FTimerHandle AttackTimerHandle;

	UPROPERTY()
	AVizParentPawn* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Attack Info")
	float AngleDistanceMultiplier;

	UPROPERTY()
	int WaveNumber;

};
