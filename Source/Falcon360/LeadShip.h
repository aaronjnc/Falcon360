// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyShip.h"
#include "Components/ActorComponent.h"
#include "LeadShip.generated.h"

class AEnemyManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALCON360_API ULeadShip : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULeadShip();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void BeginAttackRun();

	FVector GetNextPoint();

	void SetStartingPoint(AFlightPoint* FirstPoint);

	void DestroyShip();

	APawn* GetPlayer();

private:

	UPROPERTY()
	TArray<AEnemyShip*> ChildShips;

	UPROPERTY()
	TArray<USceneComponent*> FollowPoints;

	UPROPERTY()
	AEnemyManager* EnemyManager;

	UPROPERTY()
	AEnemyShip* OwningShip;
	
	UPROPERTY()
	AFlightPoint* NextPoint;

	UPROPERTY()
	FVector NextPosition;

	UPROPERTY()
	bool bAttacking;

	FVector FlyUnderLocation;
		
};
