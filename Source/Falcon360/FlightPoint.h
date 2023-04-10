// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlightPoint.generated.h"

UENUM()
enum EFlightPoints
{
	EntryPoint,
	ExitPoint,
	StopShooting,
};

UCLASS()
class FALCON360_API AFlightPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlightPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	EFlightPoints GetFlightPointType() const;

	UFUNCTION()
	AFlightPoint* GetNextPoint() const;

	UFUNCTION()
	AFlightPoint* GetPreviousPoint() const;
	
	UFUNCTION()
	TArray<AFlightPoint*> GetAdjacentPoints() const;

private:
	UPROPERTY(EditAnywhere, Category = "Point Info")
	TEnumAsByte<EFlightPoints> PointType;

	UPROPERTY(EditAnywhere, Category = "Point Info")
	AFlightPoint* PreviousPoint;
	
	UPROPERTY(EditAnywhere, Category = "Point Info")
	AFlightPoint* NextPoint;

	UPROPERTY(EditAnywhere, Category = "Point Info")
	TArray<AFlightPoint*> AdjacentPoints;
};
