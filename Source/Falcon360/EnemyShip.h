// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StructClass.h"
#include "EnemyShip.generated.h"

class AFlightPoint;
class UTurret;
class UFloatingPawnMovement;

UCLASS()
class FALCON360_API AEnemyShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetShipType(bool IsLeadShip, FEnemyShips ShipInfo);

	void SetNextPoint(AFlightPoint* NextPoint);

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UTurret* TurretComponent;

	UPROPERTY()
	float Health;

	UPROPERTY()
	float Shield;

	UPROPERTY()
	float FireRate;

	UPROPERTY()
	AFlightPoint* NextPoint;

	UPROPERTY()
	FVector NextPointPosition;

	UPROPERTY()
	bool bLeadShip;

	UPROPERTY(EditAnywhere, Category = "Overall")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Overall")
	float RotateSpeed;

	UPROPERTY()
	bool bAttacking;
};
